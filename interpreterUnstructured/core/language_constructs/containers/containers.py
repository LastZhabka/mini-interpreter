import os
import sys

sys.path.append(os.getcwd())

from interpreterUnstructured.core.language_constructs.objects.object_types import Value
from interpreterUnstructured.core.language_constructs.data_types.data_types import ValueFactory, Numerical

from abc import ABC, abstractmethod


class Container(ABC):

    @abstractmethod
    def __init__(self, elements):
        pass


class ListNumerical(Container): # Create an abstract list class and extend it (?)

    def __init__(self, elements):
        for element in elements:
            if not isinstance(element, Numerical):
                raise RuntimeError("Non numerical data in the numerical list.")
        self.__list = elements
    
    def getSum(self,):
        result = ValueFactory.createInt(0)
        for element in self.__list:
            result = result + element
        return result   
    
    def getProduct(self,):
        result = ValueFactory.createInt(1)
        for element in self.__list:
            result = result * element
        return result   
    
    def max(self,):
        max_element_lower_bound = ValueFactory.createInt(self.__list[0].getValue() - 1)
        max_element = max_element_lower_bound
        for element in self.__list:
            max_element = max_element.max(element)
        return max_element

    def min(self,):
        min_element_upper_bound = ValueFactory.createInt(self.__list[0].getValue() + 1)
        min_element = min_element_upper_bound
        for element in self.__list:
            min_element = min_element.min(element)
        return min_element
 
    def debugPrint(self,):
        for element in self.__list:
            print(element.getValue().value)


class ContainerFactory:

    def createList(list) -> ListNumerical:
        return ListNumerical(list)