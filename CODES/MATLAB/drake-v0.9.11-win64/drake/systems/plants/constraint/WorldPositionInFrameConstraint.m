�PNG

   IHDR   H   H   U��G  tIDATx��[KhA��'��eŋQ��E�=
��a�)FLP�H�`�⊊�S����=("�IB�'�&��������v_��e�����ggf3*���Lכ�W��=�fň#�Œ�Og,Y�j���g!���
�T�����m���*XC�b�f�ת���Ik �g��F��Yɱ�HF����ckv�6�~x��|nd�Q���;��Q�����sby}���CݝO�����d���7�-�! �!����w�����J��kE�$޴�?{u|�K��D�)��T�1Е[����`>��=8$%�BN��V~�#AR6% U� ��AN1I��C��o�+3pO�T�
U�B��)�^�������>�t��RJ b��h��Qȱ�Qw���P�}�eQNa	6�*	� ��*����Z�^bQ����?~��!59�X)�6(���['A�;޲9��ټ-���ȱ�?������~��Оp��,6�>�&��]~%�[�ť5��B��ʥ��"�0U7�g�oK�b�#A0|�F�A�k$��ԙ�̍��=��#�`��9�$�Y�<dESR�n�}Վ��t�x�e����t���@c:�PI�Lf�c�X1f���d���&�:&�����IL'�1/Qd�lE��&3�. ʝ$Ss�i�*yd����[{�����$/���E0���c�lG��m���wT�"*��0T;��M��6S�r�B��uDp����: ͇I5EP��V��h��,I�O>Vr��>�S]�p�[�ue1��*��\ͳ��E;;���v-��/bMiG�S�9��_�R��;��|n�sK�T�u��h� _	���m�u{��2���JQE���ۧ|&۵�?5��8�W�bS� و�  >�8R;R_��$� �*�W����[��O1 >i�ɑ��l�Ѯ�R����ꟹ��;�+��3O<u
x mYGgp۩�:��P5��#T4�1�&�H໣�A��E%%�2|O�Yv���<L������W͌����޲P-��LMY����EO�U�/�T��A��HԽ#��0�o��OE~�D�h��f�����=��v�j��Ɉm�f��ʹ����$	S��E����jp���N�v>�I��-�/�n�g�f���F���>��)�SGT _�eF����X�����ҽ�e%_Ʌ����w���9;	{W��j������RɁo��}�q�	�j��9��i��a� 5Gp]j�p��u�Sa����Ғ���	�����uc�X1f�aR*�4�o��2������V7�na\.�X�*����Z��yE�UD���uNs�,�DY�T��+4�6"���{�1bĈ#F�1bĨd�q����    IEND�B`�                                                                                    %s',obj.body_name,i,time_str);
      end
    end
  end
  
  methods
    function obj = WorldPositionInFrameConstraint(robot,body,pts,o_T_f,lb,ub,tspan)
      if(nargin < 7)
        tspan = [-inf,inf];
      end
      obj = obj@WorldPositionConstraint(robot,body,pts,lb,ub,tspan);
      obj.o_T_f = o_T_f;
      obj.f_T_o = invHT(o_T_f);
      obj.type = RigidBodyConstraint.WorldPositionInFrameConstraintType;
      if robot.getMexModelPtr~=0 && exist('constructPtrRigidBodyConstraintmex','file')
        ptr = constructPtrRigidBodyConstraintmex(RigidBodyConstraint.WorldPositionInFrameConstraintType,robot.getMexModelPtr,body,pts,o_T_f,lb,ub,tspan);
        obj.mex_ptr = ptr;
      end
    end
    
    
    
    function drawConstraint(obj,q,lcmgl)
      kinsol = doKinematics(obj.robot,q,false,false);
      pts_w = forwardKin(obj.robot,kinsol,obj.body,obj.pts);
      o_P_f = obj.o_T_f(1:3,4);
      lcmgl.glDrawAxes();
      for pt = pts_w
        lcmgl.glColor3f(0.25,0.25,0.25);
        lcmgl.sphere( pt, 0.02, 36, 36);
      end
      a = rotmat2axis(obj.o_T_f(1:3,1:3));
      lcmgl.glTranslated(o_P_f(1),o_P_f(2),o_P_f(3));
      lcmgl.glRotated(a(4)*180/pi,a(1),a(2),a(3));
      lcmgl.glDrawAxes();
      lcmgl.glColor4f(0,1,0,0.5);
      lcmgl.box((obj.lb+obj.ub)/2,obj.ub-obj.lb);
      lcmgl.switchBuffers();
    end
  end
end
