import os
import sys

sys.path.append(os.getcwd())

from interpreterUnstructured.core.language_constructs.containers.containers import ContainerFactory
from interpreterUnstructured.core.language_constructs.data_types.data_types import ValueFactory
from interpreterUnstructured.core.language_constructs.functions.function import FunctionFactory
from interpreterUnstructured.core.language_constructs.functions.function_call import FunctionCallFactory
from interpreterUnstructured.core.language_constructs.objects.object_types import ObjectFactory, VariableNameFactory


class Parser:
    # Static Parser
    def separate(target):
        result = []
        current_str, scope_depth = '', 0
        is_in_quotes = False
        for symb in target:
            if scope_depth == 0 and symb == ' ' and is_in_quotes == False:
                if len(current_str) > 0:
                    result.append(current_str)
                current_str = ''
            else:
                match symb:
                    case '(': scope_depth += 1
                    case ')': scope_depth -= 1
                    case '"': is_in_quotes = not is_in_quotes
                current_str = current_str + symb
        if len(current_str) > 0:
            result.append(current_str)
        return result
    
    def parseFunctionCall(function_call: str):
        if function_call[0] != '(':
            raise RuntimeError("Internal error: incorrect function format!")
        parsed_function_call =  Parser.separate(function_call[1:len(function_call)-1])
        function = FunctionFactory.createFunction(parsed_function_call[0])
        arguments = [Parser.parseExpression(arg_expression) for arg_expression in parsed_function_call[1:]]
        return FunctionCallFactory.createFunctionCall(function, arguments)

    def classifyExpression(expression: str):
        if expression[0] == '(':
            return "Function call"
        elif expression[0] == "\"":
            return "String"
        elif expression == "true" or expression == "false":
            return "Boolean"
        elif expression == "null":
            return "Null"
        elif expression[0] in {chr(ord('a') + letter_order) for letter_order in range(0, 26)}:
            return "Variable name"
        elif '.' in expression:
            return "Float"
        else:
            return "Int"

    def parseExpression(expression: str):
        if len(expression) == 0:
            raise RuntimeError("Interpretation error: Empty expression is given")
        match Parser.classifyExpression(expression):                                  # Add validation (?)
            case "Function call":
                return Parser.parseFunctionCall(expression)
            case "Variable name":
                return VariableNameFactory.createVariableName(expression)
            case "String":
                return ValueFactory.createString(expression[1:-1])
            case "Boolean":
                return ValueFactory.createBoolean(expression)
            case "Null":
                return ValueFactory.createNull()
            case "Float":
                return ValueFactory.createFloat(float(expression))
            case "Int":
                return ValueFactory.createInt(int(expression))