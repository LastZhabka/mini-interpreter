import os
import sys
sys.path.append(os.getcwd())

from interpreter.core.program_state.program_state_cl import ProgramState
from interpreter.core.parser.parser import Parser
from interpreter.core.language_constructs.functions.function_call import FunctionCall

class Program:
    def __init__(self, target_code: list[str]):
        self.program_state = ProgramState()
        self.target_code = target_code
        self.current_line = 0
 
    def moveToNextLine(self,):
        self.current_line += 1
        if self.current_line == len(self.target_code):
            return False
        return True
 
    def execCurrentLine(self,):
        try:
            function_call = Parser.parseExpression(self.target_code[self.current_line])
            if not isinstance(function_call, FunctionCall):
                raise Exception("Each line must be a function call.")
            function_call.execute(self.program_state)
        except Exception as e:
            print(e)
            self.program_state.logger_print(f"Error on line {self.current_line + 1}.")
            self.terminate()
        if not self.moveToNextLine():
            self.terminate()

    def terminate(self,):
        for line in self.program_state.logger.output:
            print(line)
        quit()