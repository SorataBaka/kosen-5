import sys
import math
import colorsys

def subtract(v1, v2):
    return (v1[0]-v2[0], v1[1]-v2[1], v1[2]-v2[2])

def cross_product(u, v):
    return (
        u[1]*v[2] - u[2]*v[1],
        u[2]*v[0] - u[0]*v[2],
        u[0]*v[1] - u[1]*v[0]
    )

def dot_product(v1, v2):
    return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2]

def normalize(v):
    l = math.sqrt(v[0]**2 + v[1]**2 + v[2]**2)
    if l == 0: return (0,0,0)
    return (v[0]/l, v[1]/l, v[2]/l)

def get_centroid(vertices):
    x = sum(v[0] for v in vertices) / len(vertices)
    y = sum(v[1] for v in vertices) / len(vertices)
    z = sum(v[2] for v in vertices) / len(vertices)
    return (x, y, z)


class BSPNode:
    def __init__(self, polygon_index, plane_eq):
        self.id = polygon_index
        self.plane = plane_eq 
        self.front = None
        self.back = None

def build_bsp(indices, polygons, all_vertices):
    if not indices:
        return None

    
    root_idx = indices[0]
    
    
    p0 = all_vertices[polygons[root_idx][0]]
    p1 = all_vertices[polygons[root_idx][1]]
    p2 = all_vertices[polygons[root_idx][2]]

    u = subtract(p1, p0)
    v = subtract(p2, p0)
    normal = normalize(cross_product(u, v))
    
    a, b, c = normal
    d = -dot_product(normal, p0)
    plane = (a, b, c, d)

    node = BSPNode(root_idx, plane)

    front_list = []
    back_list = []

    
    for idx in indices[1:]:
        poly_verts = [all_vertices[i] for i in polygons[idx]]
        cx, cy, cz = get_centroid(poly_verts)
        
        val = a*cx + b*cy + c*cz + d
        
        if val > 0.000001:
            front_list.append(idx)
        else:
            back_list.append(idx)

    node.front = build_bsp(front_list, polygons, all_vertices)
    node.back = build_bsp(back_list, polygons, all_vertices)
    
    return node

def print_bsp_code(node):
    if node is None:
        return

    f_id = node.front.id if node.front else -1
    b_id = node.back.id if node.back else -1
    
    print(f"  SetBspt({node.id}, {f_id}, {b_id});")
    
    print_bsp_code(node.front)
    print_bsp_code(node.back)


def parse_obj(filename):
    vertices = []
    faces = []

    try:
        with open(filename, 'r') as f:
            for line in f:
                parts = line.split()
                if not parts: continue
                
                if parts[0] == 'v':
                    vertices.append((float(parts[1]), float(parts[2]), float(parts[3])))
                elif parts[0] == 'f':
                    idxs = [int(p.split('/')[0]) - 1 for p in parts[1:]]
                    if len(idxs) == 3:
                        faces.append(idxs)
                    elif len(idxs) == 4:
                        faces.append([idxs[0], idxs[1], idxs[2]])
                        faces.append([idxs[0], idxs[2], idxs[3]])

        print("// --- Generated Data with DEBUG COLORS ---")
        print(f"  NewColors({len(faces)});")
        for i in range(len(faces)):
            
            hue = (i * 0.618033988749895) % 1.0 
            r, g, b = colorsys.hsv_to_rgb(hue, 0.8, 0.95)
            
            
            color_name = "Unknown"
            if   0.00 <= hue < 0.07: color_name = "RED"
            elif 0.07 <= hue < 0.15: color_name = "ORANGE"
            elif 0.15 <= hue < 0.20: color_name = "YELLOW"
            elif 0.20 <= hue < 0.45: color_name = "GREEN"  
            elif 0.45 <= hue < 0.55: color_name = "CYAN"
            elif 0.55 <= hue < 0.70: color_name = "BLUE"
            elif 0.70 <= hue < 0.85: color_name = "PURPLE"
            elif 0.85 <= hue < 1.00: color_name = "RED/PINK"

            
            print(f"  SetColor({i}, {r:.2f}, {g:.2f}, {b:.2f}); // Polygon {i} is {color_name}")
        
        print(f"\n  NewVertexes({len(vertices)});")
        for i, (x, y, z) in enumerate(vertices):
            print(f"  SetVertex({i}, {x:.3f}, {y:.3f}, {z:.3f});")

        
        print(f"\n  NewPolygons({len(faces)});")
        for i, f in enumerate(faces):
            
            print(f"  SetPolygon3({i}, {f[0]}, {f[1]}, {f[2]}, {i});")

        
        print(f"\n  // --- BSP Tree Configuration ---")
        all_indices = list(range(len(faces)))
        
        root_node = build_bsp(all_indices, faces, vertices)
        
        if root_node:
            print(f"  SetBsptRoot({root_node.id});")
            print_bsp_code(root_node)

    except FileNotFoundError:
        print(f"Error: File '{filename}' not found.")

if __name__ == "__main__":
    parse_obj('simple.obj')