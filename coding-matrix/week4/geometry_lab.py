from mat import Mat
import math

## Task 1
def identity(labels = {'x','y','u'}):
    '''
    In case you have never seen this notation for a parameter before,
    the way it works is that identity() now defaults to having labels 
    equal to {'x','y','u'}.  So you should write your procedure as if 
    it were defined 'def identity(labels):'.  However, if you want the labels of 
    your identity matrix to be {'x','y','u'}, you can just call 
    identity().  Additionally, if you want {'r','g','b'}, or another set, to be the
    labels of your matrix, you can call identity({'r','g','b'}).  
    '''
    res = Mat((labels,labels), dict())
    for k in list(labels):
        res.f[k,k] = 1
    return res

## Task 2
def translation(x,y):
    '''
    Input:  An x and y value by which to translate an image.
    Output:  Corresponding 3x3 translation matrix.
    '''
    res = identity()
    res['x','u'] = x
    res['y', 'u'] = y
    return res

## Task 3
def scale(a, b):
    '''
    Input:  Scaling parameters for the x and y direction.
    Output:  Corresponding 3x3 scaling matrix.
    '''
    res = identity()
    res['x', 'x'] = a
    res['y', 'y'] = b
    return res

## Task 4
def rotation(angle):
    '''
    Input:  An angle in radians to rotate an image.
    Output:  Corresponding 3x3 rotation matrix.
    Note that the math module is imported.
    '''
    res = identity()
    a = angle
    c = math.cos(a)
    s = math.sin(a)
    res['x','x'] = c
    res['x','y'] = -s
    res['y', 'x'] = s
    res['y', 'y'] = c
    return res

## Task 5
def rotate_about(x,y,angle):
    '''
    Input:  An x and y coordinate to rotate about, and an angle
    in radians to rotate about.
    Output:  Corresponding 3x3 rotation matrix.
    It might be helpful to use procedures you already wrote.
    '''
    return translation(x,y)* rotation(angle) *translation(-x, -y)

## Task 6
def reflect_y():
    '''
    Input:  None.
    Output:  3x3 Y-reflection matrix.
    '''
    res = identity()
    res['x','x'] = -1
    return res

## Task 7
def reflect_x():
    '''
    Inpute:  None.
    Output:  3x3 X-reflection matrix.
    '''
    res = identity()
    res['y','y'] = -1
    return res
    
## Task 8    
def scale_color(scale_r,scale_g,scale_b):
    '''
    Input:  3 scaling parameters for the colors of the image.
    Output:  Corresponding 3x3 color scaling matrix.
    '''
    res = identity({'r','g','b'})
    res['r','r'] = scale_r
    res['g','g'] = scale_g
    res['b', 'b'] = scale_b
    return res

## Task 9
def grayscale():
    '''
    Input: None
    Output: 3x3 greyscale matrix.
    '''
    res = identity({'r', 'g', 'b'})
    for k in res.D[1]:
        res['r', k] = 77/256
    for k in res.D[1]:
        res['g', k] = 151/256
    for k in res.D[1]:
        res['b', k] = 28/256



    return scale_color(77/256, 151/256, 28/256)

## Task 10
def reflect_about(p1,p2):
    '''
    Input: 2 points that define a line to reflect about.
    Output:  Corresponding 3x3 reflect about matrix.
    '''
    pass


