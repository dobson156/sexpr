#ifndef LISP_STRUCTURE_HPP
#define LISP_STRUCTURE_HPP

#include <memory>

namespace sexpr {

class base;
class node;
class op;
class num;
class nil;

struct visitor {
	virtual void visit(const node& n)=0;
	virtual void visit(const op& o)=0;
	virtual void visit(const num &n)=0;
	virtual void visit(const nil&)=0;
}; //struct visitor

enum class type_id { node, op, num, nil };

using base_ptr = std::unique_ptr<base>;

class base {
public:
	virtual ~base() { }

	//mutating and non mutation visitor
	virtual void accept(visitor&)=0;
	virtual void accept(visitor&) const =0;
	//void get_id();
}; //class base

class node : public base {
	base_ptr car_, cdr_;
public:
	node(base_ptr car, base_ptr cdr)
	:	car_ { std::move(car) }
	,	cdr_ { std::move(cdr) }
	{	}

	const base& car() const { return *car_; }
	const base& cdr() const { return *cdr_; }

	void accept(visitor& v) override       { v.visit(*this); }
	void accept(visitor& v) const override { v.visit(*this); }
}; //class node

enum class op_type { plus, minus, mult, div };

class op : public base {
	op_type op_type_;
public:
	op(op_type op) : op_type_ { op } { }

	op_type value() const { return op_type_; }

	void accept(visitor& v) override       { v.visit(*this); }
	void accept(visitor& v) const override { v.visit(*this); }
}; //class op

class num : public base {
	int val_;
public:
	num(int val) : val_ { val } { }
	int value() const { return val_; } 

	void accept(visitor& v) override       { v.visit(*this); }
	void accept(visitor& v) const override { v.visit(*this); }
}; //class num

class nil : public base { 
	void accept(visitor& v) override       { v.visit(*this); }
	void accept(visitor& v) const override { v.visit(*this); }
}; //class nil

} //namespace sexpr

#endif //LISP_STRUCTURE_HPP
