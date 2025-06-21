#include <regex>

/*
Rules:
(, )  => DelimiterToken(pos, symb)

add + set + puts + concat + lowercase + uppercase + lowercase +
replace + substring + subtract + multiply + divide + abs +
min + gt + lt + equal + not_equal 
=> KeywordToken

null 
=> NullLitToken

(0) | ((1 | 2 | ... | 9) + (0 | 1 | 2 | ... | 9)*) 
=> IntLitToken

(") + (not("))* + (") 
=> StringLitToken

false | true 
=> BoolLitToken

((0) | ((1 | 2 | ... | 9) + (0 | 1 | 2 | ... | 9)*)) 
+ '.' + ((0) | ((1 | 2 | ... | 9) + (0 | 1 | 2 | ... | 9)*) 
=> FloatLitToken


IdentifierToken

*/
class Lexer {
    private:
        regex lexer_rules
    public:
        
};