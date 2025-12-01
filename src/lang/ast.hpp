#ifndef AST_HPP
#define AST_HPP

#include <vector>
#include <string>
#include <memory>
#include <ostream>

enum class NodeType {
	Number,
	BinaryExpr
};

struct Node {
	virtual ~Node() = default;

	virtual NodeType type() = 0;

	virtual std::ostream& print(std::ostream& os) = 0;

	friend std::ostream& operator<<(std::ostream& os, const std::unique_ptr<Node>& node) {
		if (node) return node->print(os);
		return os << "null";
	}

};

struct Crate {
	std::vector<std::unique_ptr<Node>> body;
};

struct Number : Node {
	Number(int value) : value(value) {};

	NodeType type() { return NodeType::Number; };

	int value;

	std::ostream& print(std::ostream& os) { return os << "Number(" << value << ")"; };
};

struct BinaryExpr : Node {
	BinaryExpr(std::unique_ptr<Node> lhs, std::string op, std::unique_ptr<Node> rhs)
        : lhs(std::move(lhs)), op(op), rhs(std::move(rhs)) {}

	NodeType type() { return NodeType::BinaryExpr; };

	std::unique_ptr<Node> lhs;
	std::string op;
	std::unique_ptr<Node> rhs;

	std::ostream& print(std::ostream& os) { return os << "BinaryExpr(" << lhs << " " << op << " " << rhs << ")"; };
};

struct UnaryExpr : Node {
	UnaryExpr(std::string op, std::unique_ptr<Node> rhs)
        : op(op), rhs(std::move(rhs)) {}

	NodeType type() { return NodeType::BinaryExpr; };

	std::string op;
	std::unique_ptr<Node> rhs;

	std::ostream& print(std::ostream& os) { return os << "UnaryExpr(" << op << rhs << ")"; };
};

#endif