import os
import sys
sys.path.append(os.getcwd())

from interpreterUnstructured.core.language_constructs.containers.containers import *
from interpreterUnstructured.core.language_constructs.data_types.data_types import *
from interpreterUnstructured.core.language_constructs.objects.object_types import *
from interpreterUnstructured.core.program_state.program_state_ import ProgramState

class Arguments:

    def __init__(self, arg_types):
        self.arg_num = len(arg_types)
        self.arg_types = arg_types
    
    def validate(self, args, program_state: ProgramState):
        if len(self.arg_types) == 1 and self.arg_types[0] == ListNumerical:
            arg_types = [Numerical for _ in range(len(args))]
            arg_num = len(arg_types)
        else:
            arg_types = self.arg_types
            arg_num = self.arg_num
        if len(args) != arg_num:
            raise Exception("The number of arguments is invalid.")
        for type, arg in zip(arg_types, args):
            arg_val = arg
            if not issubclass(type, VariableName) and isinstance(arg, VariableName):
                arg_val = program_state.getVar(arg).getValue()
            if not isinstance(arg_val, type):
                raise Exception("Incorrect type of the argument.")

    def cast(self, args, program_state: ProgramState):
        self.validate(args, program_state)
        if len(self.arg_types) == 1 and self.arg_types[0] == ListNumerical:
            arg_types = [Numerical for _ in range(len(args))]
        else:
            arg_types = self.arg_types
        casted_args = []
        for type, arg in zip(arg_types, args):
            if isinstance(arg, VariableName) and issubclass(type, Value):
                casted_args.append(program_state.getVar(arg).getValue())
            elif isinstance(arg, VariableName) and issubclass(type, Variable):            
                casted_args.append(program_state.getVar(arg))
            else:                
                casted_args.append(arg)
        if len(self.arg_types) == 1 and self.arg_types[0] == ListNumerical:
            return [ContainerFactory.createList(casted_args)]
        return casted_args


class Function:

    def __init__(self, instruction, args_validator):
        self.instruction = instruction
        self.args_validator = args_validator
    
    def castArguments(self, args, program_state):
        return self.args_validator.cast(args, program_state)
    
    def execute(self, args, program_state : ProgramState):
        return getattr(PrimaryFunctionsImplementation, self.instruction)(*self.castArguments(args, program_state), program_state = program_state)


class FunctionFactory:
    allowed_instructions = ['puts', 'set', 'concat', 'lowercase', 
        'uppercase', 'replace', 'substring', 'add', 'subtract', 
        'multiply', 'divide', 'abs', 'max', 'min', 'lt', 'gt',
        'equal', 'not_equal', 'str']
    
    instruction_args = {
        'puts' : Arguments([String]),
        'set' : Arguments([VariableName, Value]),
        'concat' : Arguments([String, String]),
        'lowercase' : Arguments([String]),
        'uppercase' : Arguments([String]),
        'replace' : Arguments([String, String, String]),
        'substring' : Arguments([String, Int, Int]),
        'add' : Arguments([ListNumerical]),
        'subtract' : Arguments([Numerical, Numerical]),
        'multiply' : Arguments([ListNumerical]),
        'divide' : Arguments([Numerical, Numerical]),
        'abs' : Arguments([Numerical]),
        'max' : Arguments([ListNumerical]),
        'min' : Arguments([ListNumerical]),
        'lt' : Arguments([Numerical, Numerical]),
        'gt' : Arguments([Numerical, Numerical]),
        'equal' : Arguments([Value, Value]),
        'not_equal' : Arguments([Value, Value]),
        'str' : Arguments([Value])
    }
        
    def createFunction(function_name) -> Function:
        if not function_name in FunctionFactory.allowed_instructions:
            raise Exception("Incorrect funtion name.")
        return Function(function_name, FunctionFactory.instruction_args[function_name])
    
class PrimaryFunctionsImplementation:

    def puts(output: String, program_state : ProgramState) -> Null:
        program_state.loggerPrint(output.getValue())
        return ValueFactory.createNull()
    
    def set(variable_name: VariableName, variable_value: Value, program_state : ProgramState) -> Null:
        program_state.addVar(variable_name, variable_value)
        return ValueFactory.createNull()
    
    def concat(first: String, second: String, program_state : ProgramState) -> String:
        return first.concat(second)
    
    def lowercase(source: String, program_state : ProgramState) -> String:
        return source.lowercase()
    
    def uppercase(source: String, program_state : ProgramState) -> String :
        return source.uppercase()
    
    def replace(source: String, target: String, replacement: String, program_state : ProgramState) -> String:
        return source.replace(target, replacement)
    
    def substring(target_string: String, start: Int, end: Int, program_state : ProgramState) -> String:
        if start.min(end) < ValueFactory.createInt(0) or start.max(end) >= target_string.size():
            raise Exception("Wrong substring range.")
        return target_string.substring(start, end)
    
    def add(list: ListNumerical, program_state : ProgramState) -> Numerical:
        return list.getSum()
    
    def subtract(a: Numerical, b:Numerical, program_state : ProgramState) -> Numerical:
        return a - b
    
    def multiply(list: ListNumerical, program_state : ProgramState) -> Numerical:
        return list.getProduct()
    
    def divide(a: Numerical, b:Numerical, program_state : ProgramState) -> Numerical:
        if b == ValueFactory.createInt(0):
            raise Exception("Trying to divide by 0.")
        return a / b
    
    def abs(a: Numerical, program_state : ProgramState) -> Numerical:
        return a.abs()
    
    def max(list: ListNumerical, program_state : ProgramState) -> Numerical:
        return list.max()
    
    def min(list: ListNumerical, program_state : ProgramState) -> Numerical:
        return list.min()
    
    def lt(arg_1: Numerical, arg_2: Numerical, program_state : ProgramState) -> Boolean:
        return arg_1 < arg_2
    
    def gt(arg_1: Numerical, arg_2: Numerical, program_state : ProgramState) -> Boolean:
        return arg_1 > arg_2
    
    def equal(arg_1: Value, arg_2: Value, program_state : ProgramState) -> Boolean:
        return arg_1 == arg_2
    
    def not_equal(arg_1: Value, arg_2: Value, program_state : ProgramState) -> Boolean:
        return arg_1 != arg_2
    
    def str(arg, program_state : ProgramState) -> String:
        return arg.str()