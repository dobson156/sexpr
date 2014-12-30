#ifndef LISP_SEXPR_PARSER_HPP
#define LISP_SEXPR_PARSER_HPP

//#define BOOST_RESULT_OF_USE_DECLTYPE         1
#define BOOST_SPIRIT_NO_PREDEFINED_TERMINALS 1
//#define BOOST_SPIRIT_USE_PHOENIX_V3          1

#include <boost/phoenix/object/new.hpp>

#include <boost/spirit/include/qi.hpp>
/*
#include <boost/spirit/include/qi_lit.hpp>
#include <boost/spirit/include/qi_attr.hpp>
#include <boost/spirit/include/qi_int.hpp>
#include <boost/spirit/include/qi_space.hpp>
#include <boost/spirit/include/qi_action.hpp>
#include <boost/spirit/include/qi_grammar.hpp>
#include <boost/spirit/include/qi_symbols.hpp>
*/
#include <boost/spirit/include/phoenix.hpp>

namespace sexpr {

namespace qi = boost::spirit::qi;
namespace phx = boost::phoenix;

using base_ptr2=base*;

template<typename Iterator>
struct grammar : qi::grammar<Iterator, qi::space_type, base_ptr2()> {

	template<typename T>
	using rule = qi::rule<Iterator, qi::space_type, T()>;


	qi::symbols<char, op_type> op_sym;

	//rules, everything becomes a base
	rule<base*> op_g;
	rule<base*> num_g;
	rule<base*> nil_g;
	rule<base*> expr_content;
	rule<base*> expr;

	grammar() : grammar::base_type(expr) {
		//these are the qi elements we wish to use
		qi::int_type int_;
		qi::lit_type lit;
		qi::_1_type   _1;
		qi::_2_type   _2;
		qi::_3_type   _3;
		qi::_val_type _val;

		//supported operations
		op_sym.add("+", op_type::plus) ("-", op_type::minus)
		          ("*", op_type::mult) ("/", op_type::div)
		          ;

		//when matches, a object the type is allocated, the base* is then returned
		op_g  = op_sym [ _val = phx::new_<op>(_1)  ];
		num_g = int_   [ _val = phx::new_<num>(_1) ];
		nil_g = lit("")[ _val = phx::new_<nil>()   ];

		expr_content = 
			(   //any atom or expr followed by another list or end
				( num_g | op_g | expr ) >>  ( expr_content | nil_g )
			)
			[
				_val = phx::new_<node>(
					phx::construct<base_ptr>(_1), //car
					phx::construct<base_ptr>(_2)  //cdr
				)
			]
			;
		expr = lit('(') >> expr_content >> ')';
	}
}; //struct grammar



} //namespace sexpr

#endif //LISP_SEXPR_PARSER_HPP


		/*
		expr_content = 
			( num_g
			| ( op_g >> num_g >> num_g )
				[
					//HAHAHAAHHAHAA, good luck
					_val = phx::new_<node>(
						phx::construct<base_ptr>(_1),
						phx::construct<base_ptr>(phx::new_<node>(
							phx::construct<base_ptr>(_2),
							phx::construct<base_ptr>(phx::new_<node>(
								phx::construct<base_ptr>(_3),
								phx::construct<base_ptr>(phx::new_<nil>())
							))
						))
					)
				]
			)
			;
			*/
