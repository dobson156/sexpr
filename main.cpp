#include "structure.hpp"
#include "parse_sexpr.hpp"
#include "structure_io.hpp"
#include "lisp_eval.hpp"

#include <string>
#include <iostream>

int main() {
	std::string input;
	while(std::getline(std::cin, input)) {
		//parse code into sexprs
		auto root=sexpr::parse_sexpr(input);

		if(std::get<0>(root)) {
			try {
				//eval as lisp
				std::cout << lisp::eval(*std::get<1>(root), std::cout);
			}
			catch(const std::exception& e) {
				std::cerr << e.what() << std::endl;
			}
		}
		else {
			std::cerr << "failed to parse s-expr" << std::endl;
		}
	}
}
