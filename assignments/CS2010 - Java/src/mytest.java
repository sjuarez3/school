
public class mytest {
	public static void main(String[] args)
	{

	Position p1 = new Position(10,10);
	DictEntry d1 = new DictEntry(p1,10);
	Position p2 = new Position(7,7);
	DictEntry d2 = new DictEntry(p2,7);
	Position p3 = new Position(14,14);
	DictEntry d3 = new DictEntry(p3,14);
	Position p4 = new Position(3,3);
	DictEntry d4 = new DictEntry(p4,3);
	Position p5 = new Position(11,11);
	DictEntry d5 = new DictEntry(p5,11);
	Position p6 = new Position(8,8);
	DictEntry d6 = new DictEntry(p6,8);
	Position p7 = new Position(15,15);
	DictEntry d7 = new DictEntry(p7,15);
	Position p8 = new Position(17,17);
	DictEntry d8 = new DictEntry(p8,17);
	
	
	BinarySearchTree tree = new BinarySearchTree();
	
	DictEntry res = null;
	try {
	    tree.insert(d1);
	    tree.insert(d2);
	    tree.insert(d3);
	    tree.insert(d4);
	    tree.insert(d5);
	    tree.insert(d6);
	    tree.insert(d7);
	    tree.insert(d8);
	    res = tree.find(p1); // Look for existent data
	    if (res.getColor() == 10)
		System.out.println("Test 1 passed");
	    else System.out.println("Test 1 failed");
	}
	catch(Exception e) {
	    System.out.println("Test 1 failed");
	}
	try {
	    res = tree.find(new Position(5,5)); // Look for inexistent data
	    if (res == null) System.out.println("Test 2 passed");
	    else System.out.println("Test 2 failed");
	}
	catch(Exception e) {
	    System.out.println("Test 2 failed");
	}

	try {
	    tree.insert(d2);  // Try to insert same key twice
	    System.out.println("Test 3 failed");
	}
	catch(BSTException e) {
	    System.out.println("Test 3 passed");
	}
	catch (Exception e) {
	    System.out.println("Test 3 failed");
	}

	try {
	    tree.remove(p4);
	    res = tree.find(p4);  // Test data deletion
	    if (res == null) System.out.println("Test 4 passed");
	    else System.out.println("Test 4 failed");
	}
	catch(Exception e) {
	    System.out.println("Test 4 failed");
	}

	try {
	    tree.remove(new Position(6,6));  // Delete inexistent data
	    System.out.println("Test 5 failed");
	}
	catch(BSTException e) {
	    System.out.println("Test 5 passed");
	}
	catch (Exception e) {
	    System.out.println("Test 5 failed");
	}
	int a = tree.smallest().getColor();
	System.out.println("smallest is "+  a);
	int b = tree.largest().getColor();
	System.out.println("largest is "+ b);
	DictEntry s = tree.successor(p7);
	System.out.println(s);	
	DictEntry t = tree.predecessor(p2);
	System.out.println(t);

}
}
