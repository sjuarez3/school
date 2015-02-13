
public class BinaryNode {

	private BinaryNode left, right, parent; //left and right child node, parent node
	private DictEntry entry;				//Dictionary entry of node

	/** creates node with links to two children, parent, and stores data */ 
	public BinaryNode(DictEntry data)
	{
		this.entry = data;
		this.parent = null;
		this.left = null;
		this.right = null;
	}
	
	/** set left child to node */
	public void setLeft(BinaryNode node)
	{
		this.left = node;
	}

	/** set right child to node */
	public void setRight(BinaryNode node)
	{
		this.right = node;
	}
	
	/** set parent to node */
	public void setParent(BinaryNode node)
	{
		this.parent = node;
	}
	
	/** set entry to data*/
	public void setEntry(DictEntry data)
	{
		this.entry = data;
	}

	/** returns left child of this node */
	public BinaryNode getLeft()
	{
		return this.left;
	}

	/** returns right child of this node */
	public BinaryNode getRight()
	{
		return this.right;
	}
	
	/** returns parent of this node */
	public BinaryNode getParent()
	{
		return this.parent;
	}

	/** returns data entry of this node */
	public DictEntry getEntry()
	{
		return this.entry;
	}
}
