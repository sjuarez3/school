
public class Figure implements FigureADT {

	int id, width, height, type; //identifiers of figure
	Position pos;				 //position of figure
	BinarySearchTree tree;		//tree storing pixels of figure
	
	/** creates figure with id, width, height, type, offset
	 *  and BST */
	public Figure (int id, int width, int height, int type, Position pos){
		
		this.id = id;
		this.width = width;
		this.height = height;
		this.type = type;
		this.pos = pos;
		tree = new BinarySearchTree();
	}

	/** set type of figure to t */
	public void setType(int t) {
		this.type = t;
	}

	/** returns width of figure */
	public int getWidth() {
		return this.width;
	}

	/** returns height of figure */
	public int getHeight() {
		return this.height;
	}

	/** returns type of figure */
	public int getType() {
		return this.type;
	}

	/** returns ID of figure */
	public int getId() {
		return this.id;
	}

	/** returns offset of figure */
	public Position getOffset() {
		return this.pos;
	}

	/** sets offset of figure to value */
	public void setOffset(Position value) {
		this.pos = value;
	}

	/** inserts pixel data into figure's BST */
	public void addPixel(int x, int y, int rgb) throws BSTException {
		Position p = new Position(x,y);
		DictEntry d = new DictEntry(p, rgb); //creates new entry with values of parameters
		tree.insert(d);
	}

	/** checks if two figures overlap, returns true if they do, false otherwise */
	public boolean intersects(Figure fig) {
		
		//initialize four positions of each vertex of each figure
		Position topLeft = new Position(this.getOffset().getX(), this.getOffset().getY());
		Position topRight = new Position(this.getOffset().getX()+this.getWidth(), this.getOffset().getY());
		Position bottomLeft = new Position(this.getOffset().getX(), this.getOffset().getY()+this.getHeight());
		Position bottomRight = new Position(this.getOffset().getX()+this.getWidth(), this.getOffset().getY()+this.getHeight());
		Position topLeft2 = new Position(fig.getOffset().getX(), fig.getOffset().getY());
		Position topRight2 = new Position(fig.getOffset().getX()+fig.getWidth(), fig.getOffset().getY());
		Position bottomLeft2 = new Position(fig.getOffset().getX(), fig.getOffset().getY()+fig.getHeight());
		Position bottomRight2 = new Position(fig.getOffset().getX()+fig.getWidth(), fig.getOffset().getY()+fig.getHeight());
		
		//if this figure's vertices don't intersect with fig's vertices then return false
		if(topLeft.getX() >= bottomRight2.getX()
				|| bottomRight.getX() <= topLeft2.getX() 
				|| bottomLeft.getY() <= topRight2.getY()
				|| topRight.getY() >= bottomLeft2.getY())
			return false;
		//if this figure overlaps fig then return true
		else
			return true;
	}		
}
