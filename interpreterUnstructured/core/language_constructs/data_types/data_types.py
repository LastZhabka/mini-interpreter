from abc import ABC, abstractmethod
import math


class Value(ABC):

    @abstractmethod
    def __init__(self, value):
        pass

    @abstractmethod
    def str(self,):
        pass

    @abstractmethod
    def __eq__(self,):
        pass
 

class Null(Value):
    def __init__(self):
        pass
    def str(self,):
        return ValueFactory.createString("null")
    
    def __eq__(self, other):
        if not isinstance(other, Null):
            return ValueFactory.createBoolean(False)
        return ValueFactory.createBoolean(True)


class String(Value): # Maybe add the String to container and change this class to symb (?) 

    def __init__(self, value):
        if not isinstance(value, str):
            raise RuntimeError("Implementation error")
        self.__value = value
    
    def getValue(self,):
        return self.__value

    def size(self,):
        return ValueFactory.createInt(len(self.__value))

    def concat(self, other):
        return ValueFactory.createString(self.getValue() + other.getValue())
    
    def uppercase(self,):
        return ValueFactory.createString(self.__value.upper())
    
    def lowercase(self,):
        return ValueFactory.createString(self.__value.lower())
    
    def replace(self, target, replacement):
        return ValueFactory.createString(self.__value.replace(target.getValue(), replacement.getValue()))
    
    def substring(self, start, end):
        return ValueFactory.createString(self.__value[start.getValue():end.getValue()])
    
    def str(self,):
        return ValueFactory.createString(self.__value)
    
    def __eq__(self, other):
        if not isinstance(other, String):
            raise ValueFactory.createBoolean(False)
        return ValueFactory.createBoolean(self.__value == other.__value)
    
    def output(self,):
        print(self.__value)
 

class Boolean(Value):

    def __init__(self, value):
        self.__value = value
    
    def isTrue(self,):
        return self.__value
 
    def str(self,):
        if self.value:
            return ValueFactory.createString("true")
        return ValueFactory.createString("false")
    
    def __eq__(self, other):
        if not isinstance(other, Boolean):
            raise ValueFactory.createBoolean(False)
        return ValueFactory.createBoolean(self.__value == other.__value)
    
    def inverse(self):
        return ValueFactory.createBoolean(not self.__value)
 

class Numerical(Value):

    @abstractmethod   
    def __init__(self, value):
        pass
    
    def getValue(self,):
        return self.value
    
    def __lt__(self, other):
        return ValueFactory.createBoolean(self.value < other.value)
 
    def __gt__(self, other):
        return ValueFactory.createBoolean(self.value > other.value)
    
    def __eq__(self, other):
        if not issubclass(type(other), Numerical):
            return ValueFactory.createBoolean(False)
        return ValueFactory.createBoolean(self.value == other.value)
    
    def abs(self, ):
        return -self if self < 0 else self
 

class Int(Numerical):

    def __init__(self, value):
        self.value = int(value)

    def __add__(self, other):
        if isinstance(other, Float):
            return ValueFactory.createFloat(self.value + other.value)
        return ValueFactory.createInt(self.value + other.value)
    
    def __sub__(self, other):
        if isinstance(other, Float):
            return ValueFactory.createFloat(self.value - other.value)
        return ValueFactory.createInt(self.value - other.value)
    
    def __mul__(self, other):
        if isinstance(other, Float):
            return ValueFactory.createFloat(self.value * other.value)
        return ValueFactory.createInt(self.value * other.value)
    
    def __truediv__(self, other):
        if isinstance(other, Float):
            return ValueFactory.createFloat(self.value / other.value)
        return ValueFactory.createInt(math.trunc(self.value / other.value))
    
    def min(self, other):
        if isinstance(other, Float):
            return ValueFactory.createFloat(min(self.value, other.value))
        return ValueFactory.createInt(min(self.value, other.value))
    
    def max(self, other):
        if isinstance(other, Float):
            return ValueFactory.createFloat(max(self.value, other.value))
        return ValueFactory.createInt(max(self.value, other.value))

    def str(self,):
        return ValueFactory.createString(str(self.value))
        
        
class Float(Numerical):
    
    def __init__(self, value):
        self.value = value
 
    def __add__(self, other):
        return ValueFactory.createFloat(self.value + other.value)
    
    def __sub__(self, other):
        return ValueFactory.createFloat(self.value - other.value)
    
    def __mul__(self, other):
        return ValueFactory.createFloat(self.value * other.value)
    
    def __truediv__(self, other):
        return ValueFactory.createFloat(self.value / other.value)
    
    def min(self, other):
        return ValueFactory.createFloat(min(self.value, other.value))
    
    def max(self, other):
        return ValueFactory.createFloat(max(self.value, other.value))

    def str(self):
        str_doub = ("{:.4f}".format(self.value))
        while str_doub[-2] != '.' and str_doub[-1] == '0':
            str_doub = str_doub[:-1]
        return ValueFactory.createString(str_doub)


class ValueFactory:

    def createNull() -> Null:
        return Null()
    
    def createBoolean(value) -> Boolean:
        return Boolean(value)

    def createInt(value) -> Int:
        return Int(value)

    def createFloat(value) -> Float:
        return Float(value)

    def createString(value) -> String:
        return String(value)