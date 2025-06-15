class Logger:
    def __init__(self, ):
        self.current_line = 1
        self.output = []
    
    def print(self, output_str):
        self.output.append(output_str)