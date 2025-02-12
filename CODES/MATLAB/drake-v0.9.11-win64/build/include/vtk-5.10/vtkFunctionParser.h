                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                r VTK_PARSER_BEGIN_VARIABLES+1, VTK_PARSER_BEGIN_VARIABLES+2, ...,
// because they are used to look up variables numbered 1, 2, ...
#define VTK_PARSER_BEGIN_VARIABLES 48

// the value that is retuned as a result if there is an error
#define VTK_PARSER_ERROR_RESULT VTK_LARGE_FLOAT

class VTK_COMMON_EXPORT vtkFunctionParser : public vtkObject
{
public:
  static vtkFunctionParser *New();
  vtkTypeMacro(vtkFunctionParser, vtkObject);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Set/Get input string to evaluate.
  void SetFunction(const char *function);
  vtkGetStringMacro(Function);

  // Description:
  // Check whether the result is a scalar result.  If it isn't, then
  // either the result is a vector or an error has occurred.
  int IsScalarResult();

  // Description:
  // Check whether the result is a vector result.  If it isn't, then
  // either the result is scalar or an error has occurred.
  int IsVectorResult();

  // Description:
  // Get a scalar result from evaluating the input function.
  double GetScalarResult();

  // Description:
  // Get a vector result from evaluating the input function.
  double* GetVectorResult();
  void GetVectorResult(double result[3]) {
    double *r = this->GetVectorResult();
    result[0] = r[0]; result[1] = r[1]; result[2] = r[2]; };

  // Description:
  // Set the value of a scalar variable.  If a variable with this name
  // exists, then its value will be set to the new value.  If there is not
  // already a variable with this name, variableName will be added to the
  // list of variables, and its value will be set to the new value.
  void SetScalarVariableValue(const char* variableName, double value);
  void SetScalarVariableValue(int i, double value);

  // Description:
  // Get the value of a scalar variable.
  double GetScalarVariableValue(const char* variableName);
  double GetScalarVariableValue(int i);

  // Description:
  // Set the value of a vector variable.  If a variable with this name
  // exists, then its value will be set to the new value.  If there is not
  // already a variable with this name, variableName will be added to the
  // list of variables, and its value will be set to the new value.
  void SetVectorVariableValue(const char* variableName, double xValue,
                              double yValue, double zValue);
  void SetVectorVariableValue(const char* variableName,
                              const double values[3]) {
    this->SetVectorVariableValue(variableName,values[0],values[1],values[2]);};
  void SetVectorVariableValue(int i, double xValue, double yValue,
                              double zValue);
  void SetVectorVariableValue(int i, const double values[3]) {
    this->SetVectorVariableValue(i,values[0],values[1],values[2]);};

  // Description:
  // Get the value of a vector variable.
  double* GetVectorVariableValue(const char* variableName);
  void GetVectorVariableValue(const char* variableName, double value[3]) {
    double *r = this->GetVectorVariableValue(variableName);
    value[0] = r[0]; value[1] = r[1]; value[2] = r[2]; };
  double* GetVectorVariableValue(int i);
  void GetVectorVariableValue(int i, double value[3]) {
    double *r = this->GetVectorVariableValue(i);
    value[0] = r[0]; value[1] = r[1]; value[2] = r[2]; };

  // Description:
  // Get the number of scalar variables.
  vtkGetMacro(NumberOfScalarVariables,int);

  // Description:
  // Get the number of vector variables.
  vtkGetMacro(NumberOfVectorVariables,int);

  // Description:
  // Get the ith scalar variable name.
  char* GetScalarVariableName(int i);

  // Description:
  // Get the ith vector variable name.
  char* GetVectorVariableName(int i);

  // Description:
  // Remove all the current variables.
  void RemoveAllVariables();

  // Description:
  // Remove all the scalar variables.
  void RemoveScalarVariables();

  // Description:
  // Remove all the vector variables.
  void RemoveVectorVariables();

  // Description:
  // When ReplaceInvalidValues is on, all invalid values (such as
  // sqrt(-2), note that function parser does not handle complex
  // numbers) will be replaced by ReplacementValue. Otherwise an
  // error will be reported
  vtkSetMacro(ReplaceInvalidValues,int);
  vtkGetMacro(ReplaceInvalidValues,int);
  vtkBooleanMacro(ReplaceInvalidValues,int);
  vtkSetMacro(ReplacementValue,double);
  vtkGetMacro(ReplacementValue,double);

  // Description:
  // Check the validity of the function expression.
  void CheckExpression(int &pos, char **error);

protected:
  vtkFunctionParser();
  ~vtkFunctionParser();

  int Parse();

  // Description:
  // Evaluate the function, returning true on success, false on failure.
  bool Evaluate();

  int CheckSyntax();

  void CopyParseError(int &position, char **error);

  void RemoveSpaces();
  char* RemoveSpacesFrom(const char* variableName);
  int OperatorWithinVariable(int idx);

  int BuildInternalFunctionStructure();
  void BuildInternalSubstringStructure(int beginIndex, int endIndex);
  void AddInternalByte(unsigned char newByte);

  int IsSubstringCompletelyEnclosed(int beginIndex, int endIndex);
  int FindEndOfMathFunction(int beginIndex);
  int FindEndOfMathConstant(int beginIndex);

  int IsVariableName(int currentIndex);
  int IsElementaryOperator(int op);

  int GetMathFunctionNumber(int currentIndex);
  int GetMathFunctionNumberByCheckingParenthesis( int currentIndex );
  int GetMathFunctionStringLength(int mathFunctionNumber);
  int GetMathConstantNumber(int currentIndex);
  int GetMathConstantStringLength(int mathConstantNumber);
  unsigned char GetElementaryOperatorNumber(char op);
  unsigned char GetOperandNumber(int currentIndex);
  int GetVariableNameLength(int variableNumber);

  int DisambiguateOperators();

  vtkSetStringMacro(ParseError);

  int FindPositionInOriginalFunction(const int& pos);

  char* Function;
  char* FunctionWithSpaces;

  int FunctionLength;
  int NumberOfScalarVariables;
  int NumberOfVectorVariables;
  char** ScalarVariableNames;
  char** VectorVariableNames;
  double* ScalarVariableValues;
  double** VectorVariableValues;
  unsigned char *ByteCode;
  int ByteCodeSize;
  double *Immediates;
  int ImmediatesSize;
  double *Stack;
  int StackSize;
  int StackPointer;

  vtkTimeStamp FunctionMTime;
  vtkTimeStamp ParseMTime;
  vtkTimeStamp VariableMTime;
  vtkTimeStamp EvaluateMTime;
  vtkTimeStamp CheckMTime;

  int ReplaceInvalidValues;
  double ReplacementValue;

  int   ParseErrorPositon;
  char* ParseError;

private:
  vtkFunctionParser(const vtkFunctionParser&);  // Not implemented.
  void operator=(const vtkFunctionParser&);  // Not implemented.
};

#endif
