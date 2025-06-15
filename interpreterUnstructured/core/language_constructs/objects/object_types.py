import os
import sys
sys.path.append(os.getcwd())
from abc import ABC
from interpreterUnstructured.core.language_constructs.data_types.data_types import *

class Object(ABC):
    pass 

class Variable(Object):

    def __init__(self, name, value):
        self._name = name
        self._type = type(value)
        self._value = value # Only primitive types are allowed + String
    
    def getValue(self,):
        return self._value

    def unwrapArgs(self, args):
        new_args = (val._value if isinstance(val, Variable) else val for val in args)
        return new_args
    
    def unwrapKwargs(self, kwargs):
        unwrapped_kwargs = {key : (val._value if isinstance(val, Variable) else val) for key, val in kwargs}
        return unwrapped_kwargs

    def __getattr__(self, function_name):
        
        def targetFunction(*args, **kwargs):
            return getattr(self._value, function_name)(*self.unwrapArgs(args), **self.unwrapKwargs(kwargs))

        if hasattr(self._value, function_name):
            return targetFunction
        else:
            raise RuntimeError(f"{self.type} don't have attribute {function_name}")
 
    def __lt__(self, other):
        if not isinstance(other, (Value, Variable)):
            raise RuntimeError(f"The operation is not supported by {type(other)}")
        if isinstance(other, Value):
            return self._value < other
        return self._value < other._value
 
    def __gt__(self, other):
        if not isinstance(other, (Value, Variable)):
            raise RuntimeError(f"The operation is not supported by {type(other)}")
        if isinstance(other, Value):
            return self._value > other
        return self._value > other._value
    
    def __eq__(self, other):
        if not isinstance(other, (Value, Variable)):
            raise RuntimeError(f"The operation is not supported by {type(other)}")
        if isinstance(other, Value):
            return self._value == other
        return self._value == other._value

    def __add__(self, other):
        if not isinstance(other, (Value, Variable)):
            raise RuntimeError(f"The operation is not supported by {type(other)}")
        if isinstance(other, Value):
            return self._value == other
        return self._value + other._value
    
    def __sub__(self, other):
        if not isinstance(other, (Value, Variable)):
            raise RuntimeError(f"The operation is not supported by {type(other)}")
        if isinstance(other, Value):
            return self._value == other
        return self._value - other._value
    
    def __mul__(self, other):
        if not isinstance(other, (Value, Variable)):
            raise RuntimeError(f"The operation is not supported by {type(other)}")
        if isinstance(other, Value):
            return self._value * other
        return self._value * other._value
    
    def __truediv__(self, other):
        if not isinstance(other, (Value, Variable)):
            raise RuntimeError(f"The operation is not supported by {type(other)}")
        if isinstance(other, Value):
            return self._value * other
        return self._value / other._value
        

class ObjectFactory:
    
    def createVariable(name, value) -> Variable:
        if not isinstance(value, Value):
            raise RuntimeError(f"Incorrect variable value ({type(value)}) during initialization.")
        return Variable(name, value)
    

class VariableName:
    
    def __init__(self, variable_name):
        self.variable_name = variable_name
    
    def getName(self,) -> str:
        return self.variable_name
    
    def __hash__(self,):
        return hash(self.variable_name)
        


class VariableNameFactory:

    @staticmethod
    def isAllowedSymbol(symb) -> bool:
        if ord('a') <= ord(symb) and ord(symb) <= ord('z'):
            return True
        if ord('A') <= ord(symb) and ord(symb) <= ord('Z'):
            return True
        if ord('0') <= ord(symb) and ord(symb) <= ord('9'):
            return True
        return False
    
    @staticmethod
    def isValidName(name: str) -> bool:
        if len(name) == 0 or (not (ord('a') <= ord(name[0]) and ord(name[0]) <= ord('z'))):
            return False
        for symbol in name:
            if not VariableNameFactory.isAllowedSymbol(symbol):
                return False
        return True

    def createVariableName(name: str) -> VariableName:
        if not VariableNameFactory.isValidName(name):
            raise Exception("Invalid variable name")
        return VariableName(name)