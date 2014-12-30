#ifndef LISP_EVAL_HPP
#define LISP_EVAL_HPP

#include "structure.hpp"

#include <ostream>

namespace lisp {

/**
* is the param of child type T
* this the same as dyn_casting then testing for null
* if speed ever becomes an issue, this should be reimpl'ed with tags
* \tparam the type we are testing for
* \param b the object we wish to test
* \return whethe or not b is of type T.
*/
template<typename T> //this could be reimplemented with a tag system
bool is(const sexpr::base& b) { return dynamic_cast<const T*>(&b) != nullptr; }
template<typename T> //this could be reimplemented with a tag system
bool is(sexpr::base& b) { return dynamic_cast<T*>(&b) != nullptr; }

/**
* return the number of nodes that follow in a chain of cdrs
* ie the length of the list
* \param starting node
* \returns the size
*/
std::size_t count_elem(const sexpr::node& n);

/**
* Does this list have to the correct form for an operation expression
* ie op >> expr >> expr
* \param the start of the list
* \returns true if the list has the correct form
*/
bool is_valid_op_form(const sexpr::node& n);

/**
 * visits the various entities and numerically evaluates them
 */
class lisp_eval_visitor : public sexpr::visitor {  
	int value_;
public:
	/**
	 * the value produced from the evaluation
	 */
	int value() const;
	/**
	 * retreives the value from a num item
	 */
	void visit(const sexpr::num& n) override;
	/**
	 * evaluates the value of a list as a op expression
	 */
	void visit(const sexpr::node& n) override;
	/**
	 * currently nil evals to zero, but should possibly throw an error
	 */
	void visit(const sexpr::nil& n) override;
	/**
	 * this is empty as the work for an op is done in the context of a list
	 */
	void visit(const sexpr::op& o) override;
}; //class lisp_eval_visitor

/**
* a function which evaluate the numeric value of sexpr true when
* evaluated as lisp
*/
int eval(const sexpr::base& b, std::ostream& out);

} //namesapce lisp

#endif //LISP_EVAL_HPP
