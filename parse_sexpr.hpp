#ifndef LISP_PARSE_SEXPR_HPP
#define LISP_PARSE_SEXPR_HPP

#include "structure.hpp"

namespace sexpr {

std::pair<bool, base_ptr> parse_sexpr(const std::string& data);

} //namespace sexpr

#endif //LISP_PARSE_SEXPR_HPP
