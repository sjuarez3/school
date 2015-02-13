
public class BinarySearchTree implements BinarySearchTreeADT{

	private BinaryNode root;

	/** creates empty BST */
	public BinarySearchTree()
	{
		this.root = new BinaryNode(null);
	}

	/** returns entry of specified key */
	public DictEntry find(Position key) {

		return find(this.root, key).getEntry();
	}

	/** inserts data in tree */
	public void insert(DictEntry data) throws BSTException {

		this.insert(this.root, data.getPosition(), data.getColor());
	}

	/** removes data with specified key from tree */
	public void remove(Position key) throws BSTException {

		this.remove(this.root, key);
	}

	/** returns entry successor of key */
	public DictEntry successor(Position key) {

		return this.successor(this.root, key).getEntry();
	}

	/** returns entry predecessor of key */
	public DictEntry predecessor(Position key) {

		return this.predecessor(this.root, key).getEntry();
	}

	/** returns dictionary entry with smallest key */
	public DictEntry smallest() {

		return this.smallest(this.root).getEntry();
	}

	/** returns dictionary entry with largest key */
	public DictEntry largest() {

		return this.largest(this.root).getEntry();
	}

	/** checks if node is a leaf */
	private boolean isLeaf(BinaryNode node)
	{
		//if node has no children return true
		if (node.getLeft() == null && node.getRight() == null && node.getEntry() == null)
			return true;
		//if node is internal, return false
		else
			return false;
	}

	private BinaryNode find(BinaryNode r, Position k)
	{
		//if r is a leaf then return r
		if (this.isLeaf(r))
		{
			return r;	
		}
		else
		{
			//if key stored in r = k then return r
			if (r.getEntry().getPosition().compareTo(k) == 0)
			{
				return r;
			}
			else
			{
				//if k < key stored in r then search left subtree and return node
				if (k.compareTo(r.getEntry().getPosition()) == -1)
				{
					return find(r.getLeft(), k);
				}
				//if k > key stored in r then search right subtree and return node
				else
				{
					return find(r.getRight(), k);
				}
			}
		}
	}

	private void insert(BinaryNode r, Position k, int colour) throws BSTException
	{
		//find node supposed to store key  k
		BinaryNode p = find(r,k);

		//if p is a leaf then store dictentry in p and create two leaves of p
		if (this.isLeaf(p))
		{
			p.setEntry(new DictEntry(k, colour));
			BinaryNode lefty = new BinaryNode(null); //left leaf
			BinaryNode righty = new BinaryNode(null);//right leaf
			p.setLeft(lefty);
			p.setRight(righty);
			lefty.setParent(p);				//set left child parent to p
			righty.setParent(p);			//set right child parent to p
		}
		//if key already exists throw exception
		else
			throw new BSTException("Key already exists");
	}

	private void remove(BinaryNode r, Position k) throws BSTException
	{
		//find node supposed to store key k
		BinaryNode p = find(r,k);

		//if p is a leaf then key does not exist, throw exception
		if (this.isLeaf(p))
		{
			throw new BSTException("Key does not exist");
		}
		else
		{
			//if both children of p are leaves, delete children and make p a leaf
			if (this.isLeaf(p.getRight()) && this.isLeaf(p.getLeft()))
			{
				p.setEntry(null);
				p.setLeft(null);
				p.setRight(null);			
			}
			//if only left child of p is leaf, delete p and child and replace with other child
			else if (this.isLeaf(p.getLeft()) && !this.isLeaf(p.getRight()))
			{
				p.getParent().setRight(p.getRight());
			}
			//if only right child of p is leaf, delete p and child and replace with other child
			else if (this.isLeaf(p.getRight()) && !this.isLeaf(p.getLeft()))
			{
				p.getParent().setLeft(p.getLeft());			
			}
			//if p is internal, find smallest node of right subtree, set p to smallest, delete smallest
			else
			{
				BinaryNode s = smallest(p.getRight());
				p.setEntry(s.getEntry());
				p.setRight(s.getRight());
			}
		}
	}

	private BinaryNode smallest(BinaryNode r)
	{
		//if root is a leaf then return null
		if (this.isLeaf(r))
		{
			return null;
		}
		else
		{
			//loop through left-only branch
			BinaryNode p = r;
			while (!this.isLeaf(p))
			{
				p = p.getLeft();
			}
			//return smallest value
			return p.getParent();
		}
	}

	private BinaryNode largest(BinaryNode r)
	{
		//if root is a leaf then return null
		if (this.isLeaf(r))
		{
			return null;
		}
		else
		{
			//loop through right-only branch
			BinaryNode p = r;
			while (!this.isLeaf(p))
			{
				p = p.getRight();
			}
			//return largest value
			return p.getParent();
		}
	}

	private BinaryNode successor(BinaryNode r, Position k)
	{
		//find node storing supposed key k
		BinaryNode p = find(r,k);

		//if p and p's right child are internal, return smallest node in right subtree of p
		if (!this.isLeaf(p) && !this.isLeaf(p.getRight()))
		{
			return this.smallest(p.getRight());
		}
		else
		{
			//if p is the root return null
			if (p.equals(r))
			{
				return new BinaryNode(null);
			}
			//while p is not the root and p is the right child of its parent, set p to parent
			while (!p.equals(r) && p.equals(p.getParent().getRight()))
			{
				p = p.getParent();
			}
			//if p is the root return null
			if (p.equals(r))
			{
				return new BinaryNode(null);
			}
			//return parent of p
			else
			{
				return p.getParent();
			}
		}
	}

	private BinaryNode predecessor(BinaryNode r, Position k)
	{
		//find node storing supposed key k
		BinaryNode p = find(r,k);

		//if p and p's left child are internal, return largest node in left subtree of p
		if (!this.isLeaf(p) && !this.isLeaf(p.getLeft()))
		{
			return this.largest(p.getLeft());
		}
		else
		{
			//if p is the root return null
			if (p.equals(r))
			{
				return new BinaryNode(null);
			}
			//while p is not the root and p is the left child of its parent, set p to parent
			while (!p.equals(r) && p.equals(p.getParent().getLeft()))
			{
				p = p.getParent();
			}
			//if p is the root return null
			if (p.equals(r))
			{
				return new BinaryNode(null);
			}
			//return parent of p
			else
			{
				return p.getParent();
			}
		}
	}
}
