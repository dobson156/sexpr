#include "lisp_eval.hpp"

#include <iostream> //TODO remove

namespace lisp {

std::size_t count_elem(const sexpr::node& n) {
	//if this is the case, then the list has no content
	if(is<sexpr::nil>(n.car())) return 0;

	std::size_t i=1;
	const sexpr::base *base_cdr=&n.cdr();

	while(is<sexpr::node>(*base_cdr)) {
		base_cdr=&static_cast<const sexpr::node&>(*base_cdr).cdr();
		++i;
	}
	return i;
}

bool is_valid_op_form(const sexpr::node& n) {
	//because it's lazy, we don't actually know if those params are valid
	return is<sexpr::op>(n.car()) && count_elem(n) == 3; 
}

int lisp_eval_visitor::value() const { return value_; }

void lisp_eval_visitor::visit(const sexpr::num& n) {
	this->value_=n.value();
}
void lisp_eval_visitor::visit(const sexpr::node& n) {
	//we know that it is AT LEAST    op >> node >> node, 
	//whether those nodes eval is another matter
	if(is_valid_op_form(n)) {
		//get the op
		const sexpr::op& o = static_cast<const sexpr::op&>(n.car());
		//get the params
		const auto& node1 = static_cast<const sexpr::node&>(n.cdr());
		const auto& node2 = static_cast<const sexpr::node&>(node1.cdr());

		int arg1=eval(node1.car(), std::cout),
			arg2=eval(node2.car(), std::cout);

		switch(o.value()) {
		case sexpr::op_type::plus:  this->value_ = arg1 + arg2; break;
		case sexpr::op_type::minus: this->value_ = arg1 - arg2; break;
		case sexpr::op_type::mult:  this->value_ = arg1 * arg2; break;
		case sexpr::op_type::div:   this->value_ = arg1 / arg2; break;
		}
	}
	else throw std::runtime_error("list is not in valid form to evaluate");
}

void lisp_eval_visitor::visit(const sexpr::nil& n) { this->value_ = 0; }
void lisp_eval_visitor::visit(const sexpr::op& o) { 
	throw std::runtime_error("operators must be prefix");
}
int eval(const sexpr::base& b, std::ostream& out) {
	lisp_eval_visitor lev;
	b.accept(lev);
	return lev.value();
}

} //namesapce lisp
