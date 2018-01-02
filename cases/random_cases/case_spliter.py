import random

def generate_case(path, quant):
    f = open(path)
    case = []
    for i in f:
        case.append(i)

    ns = int(case[4].split(" = ")[1])
    nv = int(case[5].split(" = ")[1])
    no = int(case[6].split(" = ")[1])
    intervals = [(0, ns-1), (ns, ns + nv-1), (ns + nv, ns + nv + no-1)]

    new_case = ""
    new_case += case[0] + case[1] + case[2] + case[3]
    new_case += "#RoutedShapes = " + str(quant[0]) + "\n"
    new_case += "#RoutedVias = " + str(quant[1]) + "\n"
    new_case += "#Obstacles = " + str(quant[2]) + "\n"

    case = case[7:]

    shapes = case[intervals[0][0]:intervals[0][1]+1]
    vias = case[intervals[1][0]:intervals[1][1]+1]
    obstacles = case[intervals[2][0]:intervals[2][1]+1]

    for i in range(quant[0]):
        new_case += shapes.pop(random.randint(0, len(shapes) - 1))

    for i in range(quant[1]):
        new_case += vias.pop(random.randint(0, len(vias) - 1))

    for i in range(quant[2]):
        new_case += obstacles.pop(random.randint(0, len(obstacles) - 1))

    return new_case


new_case = generate_case("../case1", (3, 3, 3))
print(new_case)
