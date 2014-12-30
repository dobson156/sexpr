#include "structure.hpp"
#include "structure_io.hpp"

namespace sexpr {

void print_visitor::visit(const node& n) {
	bool is_head = 0 == i;
	++i;

	if(is_head) os_ << "( ";

	//if this is a new list, we need to show braces
	print_visitor pv { os_ };
	n.car().accept(pv);

	os_ << " ";

	n.cdr().accept(*this);

	if(is_head) os_ << " )";
}

void print_visitor::visit(const op& o) {
	switch(o.value()) {
	case op_type::plus: os_ << "+"; break;
	case op_type::minus: os_ << "-"; break;
	case op_type::mult: os_ << "*"; break;
	case op_type::div: os_ << "/"; break;
	}
}

void print_visitor::visit(const num &n) {
	os_ << n.value();
}

void print_visitor::visit(const nil&) { }

} //namespace sexpr
