/*

Program -> Expression Program'
Program' -> \SpaceToken Program | \EOFToken

Expression -> \DelimiterToken(() Function \SpaceToken Params \DelimiterToken()) | Literal
Function -> \KeywordToken(add)|...|\KeywordToken(not_equal)
Params -> Expression \SpaceToken Params
Literal -> \IntLitToken(...) | \BoolLitToken(...) | \FloatLitToken(...) | \StringLitToken(...) | \IdentifierToken


First(Literal) = {\IntLitTOken(...), \BoolLitToken(...), \FloatLitToken(...), \StringLitToken(...), \IdentifierToken}

First(Expression) = {\DelimiterToken((), \IntLitToken(...), \BoolLitToken(...), 
                     \FloatLitToken(...), \StringLitToken(...), \IdentifierToken}

First(Function) = {\KeywordToken(...)}

First(Params) = {\DelimiterToken((), \IntLitToken(...), \BoolLitToken(...), 
                 \FloatLitToken(...), \StringLitToken(...), \IdentifierToken}

First(Program) = {\DelimiterToken((), \IntLitToken(...), \BoolLitToken(...), {\SpaceToken},
                  \FloatLitToken(...), \StringLitToken(...), \IdentifierToken}

First(Program') = {\SpaceToken, \EOFToken}

*/