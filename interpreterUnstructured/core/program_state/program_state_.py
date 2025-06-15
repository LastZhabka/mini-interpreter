import os
import sys
sys.path.append(os.getcwd())

from interpreterUnstructured.core.program_state.logger.logger import Logger
from interpreterUnstructured.core.program_state.symbol_table.symbol_table import SymbolTable, VariableName
from interpreterUnstructured.core.language_constructs.data_types.data_types import Value


class ProgramState:
    def __init__(self,):
        self.logger = Logger()
        self.symbol_table = SymbolTable()
        
        
    def loggerPrint(self, output):
        self.logger.print(output)

    def addVar(self, var_name: VariableName, var_value: Value):
        self.symbol_table.addVar(var_name, var_value)
        
    def getVar(self, var_name: VariableName):
        return self.symbol_table.getVar(var_name)
