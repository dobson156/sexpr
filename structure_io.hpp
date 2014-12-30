#include <ostream>
#include <type_traits>

namespace sexpr {

class print_visitor : public visitor {
	std::ostream& os_;
	unsigned i { 0u };
public:
	print_visitor(std::ostream& os) : os_ { os } { }

	void visit(const node& n) override;
	void visit(const op& o) override;
	void visit(const num &n) override;
	void visit(const nil&) override;
};

/**
 * Stream operator for all objects that decend from base
 * This has been implemented as a visitor
 */
template<
	typename NodeType,
	typename = typename std::enable_if_t<std::is_base_of<base, NodeType>::value>
>
std::ostream& operator<<(std::ostream& os, const NodeType& n) {
	print_visitor pv { os };
	n.accept(pv);
	return os;
}

} //namespace sexpr
