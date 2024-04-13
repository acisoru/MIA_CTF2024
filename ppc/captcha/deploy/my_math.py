import random
import ast
import operator

def generate_expr():
    ops = ["+", "-", "*"]
    a = random.randint(1, 10)
    b = random.randint(1, 10)
    c = random.randint(1, 10)
    d = random.randint(1, 10)
    e = random.randint(1, 10)
    op1 = random.choice(ops)
    op2 = random.choice(ops)
    op3 = random.choice(ops)
    op4 = random.choice(ops)
    expr = f"{a} {op1} {b} {op2} {c} {op3} {d} {op4} {e}"

    return expr

def eval_expr(expr):
    tree = ast.parse(expr, mode='eval')

    ops = {
        ast.Add: operator.add,
        ast.Sub: operator.sub,
        ast.Mult: operator.mul,
        ast.Div: operator.truediv,
        ast.USub: operator.neg,
    }

    def eval_node(node):
        if isinstance(node, ast.Num):
            return node.n
        elif isinstance(node, ast.BinOp):
            left = eval_node(node.left)
            right = eval_node(node.right)
            return ops[type(node.op)](left, right)
        elif isinstance(node, ast.UnaryOp):
            return ops[type(node.op)](eval_node(node.operand))
        else:
            raise TypeError(f"Unsupported node type: {type(node)}")
        
    return eval_node(tree.body)