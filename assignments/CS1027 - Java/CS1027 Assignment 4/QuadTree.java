/**
 * QuadTree is a class that models a QuadTree data structure.
 * @author Steve Juarez
 *
 */
public class QuadTree{

	private MyPicture picture; /** picture that will be used*/
	private QuadNode rootNode; /** root of tree*/
	private double RedT, GreenT, BlueT; /** red, green, and blue values tree*/
	private int maxLevel; /** highest level of tree*/
	
	/**
	 * Constructor that creates a Quadtree data structure recursively by splitting nodes
	 * into four QuadNodes based on the homogeneity criteria.
	 * @param pic picture to be used
	 * @param root initial QuadNode to be split
	 * @param maxLevel highest level of QuadTree
	 * @param RedT red value
	 * @param GreenT green value
	 * @param BlueT blue value
	 */
	public QuadTree(MyPicture pic, QuadNode root, int maxLevel, double RedT, double GreenT, double BlueT)
	{
		this.picture = pic;
		this.rootNode = root;
		this.maxLevel = maxLevel;
		this.RedT = RedT;
		this.GreenT = GreenT;
		this.BlueT = BlueT;
		
		// if homogeneity criteria not met, split node into four children nodes
		if (isHomogeneous(root) == false)
			this.split(root);
	}

	/**
	 * Preorder tree traversal, enqueuing nodes simultaneously.
	 * @param node node to be enqueued
	 * @param temp LinkedQueue of QuadNodes
	 * @return LinkedQueue<QuadNode> returns the LinkedQueue of QuadNodes created
	 */
	public LinkedQueue<QuadNode> preorder(QuadNode node, LinkedQueue<QuadNode> temp)
	{
		if (node != null)
		{
			temp.enqueue(node);
			preorder(node.northWest, temp);
			preorder(node.northEast, temp);
			preorder(node.southWest, temp);
			preorder(node.southEast, temp);
		}
		return temp;
	}
	
	/**
	 * Draws white squares where nodes are located from a queue.
	 * @param pic picture to be drawn on
	 * @param queue queue of nodes used to draw squares
	 */
	public void drawSegmentation(MyPicture pic, LinkedQueue<QuadNode> queue)
	{
		//loop through queue, dequeue node, draw square, then re-enqueue node
		for (int i = 0; i < queue.size(); i++)
		{
		QuadNode temp = queue.dequeue();
		pic.drawWhiteSquare(temp.getX(), temp.getY(), temp.getSideLength());
		queue.enqueue(temp);
		}
	}

	/**
	 * Paints squares an average colour of the pixels in the area.
	 * @param pic picture to be painted on
	 * @param queue queue of nodes used to be painted
	 */
	public void paintSquares(MyPicture pic, LinkedQueue<QuadNode> queue)
	{
		//loop through queue, dequeue node, paint square, then re-enqueue node
		for (int i = 0; i < queue.size(); i++)
		{
		QuadNode temp = queue.dequeue();
		pic.paintSegment(temp.getX(), temp.getY(), temp.getSideLength(), temp.getMeanRed(), temp.getMeanGreen(), temp.getMeanBlue());
		queue.enqueue(temp);
		}
	}
	
	/**
	 * Determines if a node is a leaf or not.
	 * @param node node to be checked
	 * @return boolean returns true if leaf, false if not
	 */
	public boolean isLeaf(QuadNode node)
	{
		//if node has parent and no children return true, else return false
		if (node.getParent() != null && node.getNorthEast() == null && node.getNorthWest() == null
				&& node.getSouthEast() == null && node.getSouthWest() == null)
			return true;
		else
			return false;
	}
	
	/**
	 * Determines if node passes homogeneity criteria.
	 * @param node node to be checked
	 * @return boolean returns true is is homogeneous, false if not
	 */
	public boolean isHomogeneous(QuadNode node)
	{
		//if node's RGB values are less than or equal to QuadTree's RGB values or node's level is
		//equal to QuadTree's max level return true, else return false
		if ((node.sigmaRed <= RedT && node.sigmaGreen <= GreenT && node.sigmaBlue <= BlueT)
				|| node.level == maxLevel)
			return true;
		else
			return false;
	}
	
	/**
	 * Splits node into four QuadNodes, recursively splits
	 * nodes again if homogeneity criteria is failed.
	 * @param node node to be split
	 */
	public void split(QuadNode node)
	{
		//if node is not null, create four QuadNodes, set them to be original node's
		//children, recursively continue this using newly created children nodes
		if (node != null)
		{
		QuadNode nw = new QuadNode(picture, node.getX(), node.getY(), node.sideLength/2, node.getLevel()+1, picture.simpleStatistics(node.getX(), node.getY(), node.getSideLength()/2));
		node.setNorthWest(nw);
		if (isHomogeneous(nw) == false)
			split(node.northWest);
		QuadNode ne = new QuadNode(picture, node.getX() + node.sideLength/2, node.getY(), node.sideLength/2, node.getLevel()+1, picture.simpleStatistics(node.getX() + node.sideLength/2, node.getY(), node.getSideLength()/2));
		node.setNorthEast(ne);
		if (isHomogeneous(ne) == false)
			split(node.northEast);
		QuadNode sw = new QuadNode(picture, node.getX(), node.getY() + node.sideLength/2, node.sideLength/2, node.getLevel()+1, picture.simpleStatistics(node.getX(), node.getY() + node.sideLength/2, node.getSideLength()/2));
		node.setSouthWest(sw);
		if (isHomogeneous(sw) == false)
			split(node.southWest);
		QuadNode se = new QuadNode(picture, node.getX() + node.sideLength/2, node.getY() + node.sideLength/2, node.sideLength/2, node.getLevel()+1, picture.simpleStatistics(node.getX() + node.sideLength/2, node.getY() + node.sideLength/2, node.getSideLength()/2));
		node.setSouthEast(se);
		if (isHomogeneous(se) == false)
			split(node.southEast);
		}
	}
}