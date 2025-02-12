function [frame_knots, zmp_knots] = planSwingPitched(biped, stance, swing1, swing2, initial_hold_time, target_frame_id)
% Compute a collision-free swing trajectory for a single foot.
if nargin < 5
  initial_hold_time = 0;
end

assert(swing1.frame_id == swing2.frame_id, 'planSwing expects to plan a swing trajectory between two positions of the /same/ foot body')
sizecheck(stance.pos, [7, 1]);
sizecheck(swing1.pos, [7, 1]);
sizecheck(swing2.pos, [7, 1]);

params = struct(swing2.walking_params);
params = applyDefaults(params, biped.default_walking_params);

DEBUG = false;
DEFAULT_FOOT_PITCH = pi/8; % The amount by which the swing foot pitches forward during walking

APEX_FRACTIONS = [0.15, 0.85]; % We plan only two poses of the foot during the aerial phase of the swing.
                               % Those poses are planned for locations where the toe has traveled a given
                               % fraction of the distance from its initial location to its final location.

FOOT_YAW_RATE = 0.375; % rad/s
MIN_STEP_TIME = 0.75; %s

MIN_DIST_FOR_PITCHED_SWING = 0.4;

if stance.frame_id == biped.foot_frame_id.right
  stance_foot_name = 'right';
else
  stance_foot_name = 'left';
end
if swing1.frame_id == biped.foot_frame_id.right
  swing_foot_name = 'right';
else
  swing_foot_name = 'left';
end

xy_dist = norm(swing2.pos(1:2) - swing1.pos(1:2));

% terrain_slice = double(swing2.terrain_pts);
% terrain_slice = [[0;swing1.pos(3)], terrain_slice, [xy_dist; swing2.pos(3)]];
% terrain_pts_in_local = [terrain_slice(1,:); zeros(1, size(terrain_slice, 2)); 
%                         terrain_slice(2,:) - swing1.pos(3)]

% Transform to world coordinates
T_local_to_world = [[rotmat(atan2(swing2.pos(2) - swing1.pos(2), swing2.pos(1) - swing1.pos(1))), [0;0];
                     0, 0, 1], [swing1.pos(1:2); 0]; 
                    0, 0, 0, 1];

% Determine how much of a forward step this is
R = quat2rotmat(stance.pos(4:7));
swing_distance_in_local = (swing2.pos(1:3) - swing1.pos(1:3))' * (R * [1;0;0]);

if swing_distance_in_local > MIN_DIST_FOR_PITCHED_SWING
  toe_off_angle = DEFAULT_FOOT_PITCH;
else
  toe_off_angle = 0;
end

swing_body_index = biped.foot_body_id.(swing_foot_name);
stance_body_index = biped.foot_body_id.(stance_foot_name);
% swing_toe_points_in_foot = biped.getBody(swing_body_index).getTerrainContactPoints('toe');
T_sole_to_foot = biped.getFrame(swing1.frame_id).T;
if target_frame_id.(swing_foot_name) < 0
  T_frame_to_foot = biped.getFrame(target_frame_id.(swing_foot_name)).T;
else
  T_frame_to_foot = eye(4);
end
T_toe_to_foot = biped.getFrame(biped.toe_frame_id.(swing_foot_name)).T;

T_swing1_sole_to_world = ...
  [quat2rotmat(swing1.pos(4:7)),swing1.pos(1:3); zeros(1, 3), 1];
T_swing1_frame_to_world = T_swing1_sole_to_world/T_sole_to_foot * T_frame_to_foot;

T_swing2_sole_to_world = ...
  [quat2rotmat(swing2.pos(4:7)),swing2.pos(1:3); zeros(1, 3), 1];
T_swing2_frame_to_world = T_swing2_sole_to_world/T_sole_to_foot * T_frame_to_foot;

toe1 = tform2poseQuat(T_swing1_frame_to_world/T_frame_to_foot * T_toe_to_foot);
toe2 = tform2poseQuat(T_swing2_frame_to_world/T_frame_to_foot * T_toe_to_foot);

quat_toe_off = rotmat2quat(T_swing1_frame_to_world(1:3,1:3) * rpy2rotmat([0;toe_off_angle;0]));
quat_swing2 = rotmat2quat(T_swing2_frame_to_world(1:3,1:3));

if DEBUG
  v = biped.constructVisualizer();
  v.draw(0, q_latest);
end

T_stance_sole_to_foot = biped.getFrame(stance.frame_id).T;
if target_frame_id.(stance_foot_name) < 0
  T_stance_frame_to_foot = biped.getFrame(target_frame_id.(stance_foot_name)).T;
else
  T_stance_frame_to_foot = eye(4);
end
T_stance_sole_to_world = poseQuat2tform(stance.pos);
T_stance_frame_to_world = T_stance_sole_to_world / T_stance_sole_to_foot * T_stance_frame_to_foot;

instep_shift = [0.0;stance.walking_params.drake_instep_shift;0];
zmp1 = shift_step_inward(biped, stance, instep_shift);

hold_time = params.drake_min_hold_time;

v = quat2rotmat(stance.pos(4:7)) * [0;0;1];
b = -v' * stance.pos(1:3);
support_options.support_surface = {[v;b]};
support_options.contact_groups =  {stance.walking_params.support_contact_groups};
zmp_knots = struct('t', initial_hold_time + (hold_time / 2),...
 'zmp', zmp1, ...
 'supp', RigidBodySupportState(biped, stance_body_index, support_options));

swing1_frame_pose = tform2poseQuat(T_swing1_frame_to_world);
swing2_frame_pose = tform2poseQuat(T_swing2_frame_to_world);
stance_frame_pose = tform2poseQuat(T_stance_frame_to_world);
frame_knots = struct('t', zmp_knots(end).t, ...
                           swing_foot_name, [swing1_frame_pose(1:3); quat2expmap(swing1_frame_pose(4:7)); zeros(6,1)], ...
                           stance_foot_name, [stance_frame_pose(1:3); quat2expmap(stance_frame_pose(4:7)); zeros(6,1)], ...
                           'toe_off_allowed', struct(swing_foot_name, false, stance_foot_name, false));

function add_frame_knot(swing_pose, speed)
  if nargin < 2
    speed = params.step_speed/2;
  end
  frame_knots(end+1).(swing_foot_name) = [swing_pose(1:3); quat2expmap(swing_pose(4:7)); zeros(6,1)];
  frame_knots(end).(swing_foot_name)(4:6) = closestExpmap(frame_knots(end-1).(swing_foot_name)(4:6), frame_knots(end).(swing_foot_name)(4:6));
  frame_knots(end).(stance_foot_name) = [stance_frame_pose(1:3); quat2expmap(stance_frame_pose(4:7)); zeros(6,1)];
  cartesian_distance = norm(frame_knots(end).(swing_foot_name)(1:3) - frame_knots(end-1).(swing_foot_name)(1:3));
  yaw_distance = abs((frame_knots(end).(swing_foot_name)(4:6) - frame_knots(end-1).(swing_foot_name)(4:6))' * [0;0;1]);
  dt = max([cartesian_distance / speed,...
            yaw_distance / FOOT_YAW_RATE]);
  frame_knots(end).t = frame_knots(end-1).t + dt;
  frame_knots(end).toe_off_allowed = struct(swing_foot_name, false, stance_foot_name, false);
end

% terrain_pts_in_world = T_toe_local_to_world \ terrain_pts_in_toe_local;
% max_terrain_ht_in_world = max(terrain_pts_in_world(3,:))
if ~isempty(swing2.terrain_pts)
  max_terrain_ht_in_world = double(max(swing2.terrain_pts(2,:)));
else
  max_terrain_ht_in_world = -inf;
end
% Apex knot 1
toe_apex1_in_world = (1-APEX_FRACTIONS(1))*toe1(1:3) + APEX_FRACTIONS(1)*toe2(1:3);
initial_pose_not_flat = norm(cross(T_swing1_sole_to_world(1:3,1:3) * [0;0;1], [0;0;1])) >= sin(7.5*pi/180);
if (initial_pose_not_flat || max_terrain_ht_in_world > toe_apex1_in_world(3) + params.step_height/4) && (~params.prevent_swing_undershoot)
  toe_apex1_in_world = [toe1(1:2); max_terrain_ht_in_world + params.step_height];
else
  toe_apex1_in_world(3) = max([toe_apex1_in_world(3) + params.step_height,...
                               max_terrain_ht_in_world + params.step_height]);
end
T_apex1_toe_to_world = poseQuat2tform([toe_apex1_in_world(1:3); quat_toe_off]);
T_apex1_frame_to_world = T_apex1_toe_to_world / T_toe_to_foot * T_frame_to_foot;
add_frame_knot(tform2poseQuat(T_apex1_frame_to_world));

% Apex knot 2
toe_apex2_in_world = (1-APEX_FRACTIONS(2))*toe1(1:3) + APEX_FRACTIONS(2)*toe2(1:3);
final_pose_not_flat = norm(cross(T_swing2_sole_to_world(1:3,1:3) * [0;0;1], [0;0;1])) >= sin(7.5*pi/180);
if (final_pose_not_flat || max_terrain_ht_in_world > toe_apex2_in_world(3) + params.step_height/4) && (~params.prevent_swing_overshoot)
  toe_apex2_in_world = [toe2(1:2); max_terrain_ht_in_world + params.step_height];
else
  toe_apex2_in_world(3) = max([toe_apex2_in_world(3) + params.step_height,...
                               max_terrain_ht_in_world + params.step_height]);
end
T_apex2_toe_to_world = poseQuat2tform([toe_apex2_in_world(1:3); quat_swing2]);
T_apex2_frame_to_world = T_apex2_toe_to_world / T_toe_to_foot * T_frame_to_foot;
add_frame_knot(tform2poseQuat(T_apex2_frame_to_world));

% Landing knot
add_frame_knot(swing2_frame_pose);
% add_foot_origin_knot(swing2_origin_pose, min(params.step_speed, MAX_LANDING_SPEED)/2);
if frame_knots(end).t - frame_knots(1).t < MIN_STEP_TIME
  frame_knots(end).t = frame_knots(1).t + MIN_STEP_TIME;
end


zmp_knots(end+1).t = frame_knots(end).t;
zmp_knots(end).zmp = zmp1;

v_stance = quat2rotmat(stance.pos(4:7)) * [0;0;1];
b_stance = -v_stance' * stance.pos(1:3);
v_swing = quat2rotmat(swing2.pos(4:7)) * [0;0;1];
b_swing = -v_swing' * swing2.pos(1:3);
sutriangle>
          <v1>18295</v1>
          <v2>18294</v2>
          <v3>18297</v3>
        </triangle>
        <triangle>
          <v1>18196</v1>
          <v2>18298</v2>
          <v3>18296</v3>
        </triangle>
        <triangle>
          <v1>18299</v1>
          <v2>18296</v2>
          <v3>18298</v3>
        </triangle>
        <triangle>
          <v1>18194</v1>
          <v2>18196</v2>
          <v3>18296</v3>
        </triangle>
        <triangle>
          <v1>18297</v1>
          <v2>18296</v2>
          <v3>18299</v3>
        </triangle>
        <triangle>
          <v1>18198</v1>
          <v2>18300</v2>
          <v3>18298</v3>
        </triangle>
        <triangle>
          <v1>18301</v1>
          <v2>18298</v2>
          <v3>18300</v3>
        </triangle>
        <triangle>
          <v1>18196</v1>
          <v2>18198</v2>
          <v3>18298</v3>
        </triangle>
        <triangle>
          <v1>18299</v1>
          <v2>18298</v2>
          <v3>18301</v3>
        </triangle>
        <triangle>
          <v1>18200</v1>
          <v2>18302</v2>
          <v3>18300</v3>
        </triangle>
        <triangle>
          <v1>18303</v1>
          <v2>18300</v2>
          <v3>18302</v3>
        </triangle>
        <triangle>
          <v1>18198</v1>
          <v2>18200</v2>
          <v3>18300</v3>
        </triangle>
        <triangle>
          <v1>18301</v1>
          <v2>18300</v2>
          <v3>18303</v3>
        </triangle>
        <triangle>
          <v1>18202</v1>
          <v2>18304</v2>
          <v3>18302</v3>
        </triangle>
        <triangle>
          <v1>18305</v1>
          <v2>18302</v2>
          <v3>18304</v3>
        </triangle>
        <triangle>
          <v1>18200</v1>
          <v2>18202</v2>
          <v3>18302</v3>
        </triangle>
        <triangle>
          <v1>18303</v1>
          <v2>18302</v2>
          <v3>18306</v3>
        </triangle>
        <tri