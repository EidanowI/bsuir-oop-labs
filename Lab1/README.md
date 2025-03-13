# Lab 1

Completed by Fiodar Kavalchuk, group 353504

## Functional requirements

The program must be able to:

- draw 3 types of figures: rectangle, triangle, ellipse
- delete an object
- move object
- choose fill char for object
- save canvas as a file
- load canvas from file
- undo/redo action

_Warning: all numeric input values must be integers. If something goes wrong
error will be shown in the screen._

_Objects may be displayed with altered proportions due to the
peculiarities of console output._

_You need to set the console size to 140 by 41 chars and aligning to center._

### Menu

* _Q_ - exit (without saving)
* _A_ - choose figure for adding
    * _E_ - ellipse
    * _R_ - rectangle
    * _T_ - triangle
    * _Q_ - exit
* _D_ - delete object
* _M_ - move object
* _F_ - fill object
* _S_ - save canvas
* _L_ - load canvas

### Drawing

Coordinate axes for figures come from the upper left
corner to the right and down. 
You must select the type of figure, after which you must enter the parameters for constructing the figure.

### Choosing existing objects

If the function requires selecting an object for its operation, the user will need to select an object from the list of previously created ones by entering its index.

### Moving objects

If you select the move function, you will need to select an object, after which you enter the coordinates for how far to move it.

### Deleting objects

After selecting an object, you can delete it.

### Fill object

After selecting an object, you can enter a char to fill it with.

### Saving/Loading file

Opened dialog window to choose directory.
