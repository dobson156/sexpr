#include "parse_sexpr.hpp"
#include "sexpr_parser.hpp"

#include <boost/spirit/include/qi_parse.hpp>

#include <iostream>

namespace sexpr {

namespace qi = boost::spirit::qi;

std::pair<bool, base_ptr> parse_sexpr(const std::string& data) {
	auto first=begin(data), last=end(data);

	base* root_ptr { nullptr };

	bool r = qi::phrase_parse(
		first, last, 
		grammar<decltype(first)> { }, 
		qi::space_type{},
		root_ptr
	);

	//std::cout << ( r ? "passed" : "failed" ) << std::endl;

	return std::make_pair(r, std::unique_ptr<base> { root_ptr });
}

} //namespace sexpr
