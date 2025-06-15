import os
import sys
sys.path.append(os.getcwd())

from interpreterUnstructured.core.language_constructs.data_types.data_types import Value
from interpreterUnstructured.core.language_constructs.objects.object_types import ObjectFactory, VariableName



class SymbolTable:

    def __init__(self):
        self.variables = {}
 
    def addVar(self, variable_name: VariableName, value: Value):
        # value is in value type class form 
        if variable_name.getName() in self.variables:
            raise Exception("Trying to initialize existing variable")
        self.variables.update({variable_name.getName() : ObjectFactory.createVariable(variable_name, value)})
    
    def getVar(self, variable_name: VariableName):
        if not (variable_name.getName() in self.variables):
            raise Exception(f"Trying to use uninitialized variable name : {variable_name.getName()}")
        return self.variables[variable_name.getName()]