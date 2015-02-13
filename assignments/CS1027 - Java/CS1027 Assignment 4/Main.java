public class Main{

public static void main(String[] args) {

double RedT=30;
double GreenT=30;
double BlueT=30;
int maxLevel=5;
System.out.println("Color Thresholds:");
System.out.format("RedT=%9.3f GreenT=%9.3f BlueT=%9.3f\n",RedT,GreenT,BlueT);
String redStg=Double.toString(RedT);
String greenStg=Double.toString(GreenT);
String blueStg=Double.toString(BlueT);
System.out.println("redStg=" + redStg + " greenStg=" + greenStg + " blueStg=" + blueStg);

// Display the original image
String fileName = "mando.jpg";
MyPicture pic0 = new MyPicture(fileName);
pic0.setOriginUpperLeft();
pic0.show();

// Read the image that we will segment using the quadtree
System.out.println("File:" + fileName);
MyPicture pic = new MyPicture(fileName);
// (0,0) is in the upperleft part of the window
pic.setOriginUpperLeft();
String segmented_filename="segmented-level-" + 6 + "-" + redStg + "-" + greenStg + 
                          "-" + blueStg + "-" + fileName;
String painted_filename="painted-level-" + 6 + "-" + redStg + "-" + greenStg + 
                        "-" + blueStg + "-" + fileName;

int sideLength=pic.width();
System.out.println("sideLength=" + sideLength);
int n=log2(sideLength);
System.out.println("Maximum number of levels n=" + n);
int level=0; // root
System.out.println("maxLevel=" + maxLevel);

double[] parameters = new double[6];
parameters=pic.simpleStatistics(0,0,sideLength);
pic.prettyPrintStatistics(0,0,sideLength,parameters);

// The entire image is the root node of the quadtree
QuadNode root = new QuadNode(pic,0,0,sideLength,level,parameters);
System.out.println("\nroot node generated for entire image\n");
System.out.println("root.getSideLength():" + root.getSideLength());
System.out.flush();

// Construct a full QuadTree, specifying the pic MyPicture object, 
//the root QuadNode and the maximum number of levels in the tree, maxLevel
QuadTree tree = new QuadTree(pic,root,maxLevel,RedT,GreenT,BlueT);
// Make an empty queue of QuadNode nodes
LinkedQueue<QuadNode> queue = new LinkedQueue<QuadNode>();
// Preorder traverse the tree (root, left subtree, next left subtree,
// third left subtree and fourth right subtree: if a node is a leaf
// node enqueue it onto the queue
queue=tree.preorder(root,queue);
System.out.println("\nQueue of leaf node generated via preorder()\n");

// Draw the segmentation represented by the leaf nodes in the queue
tree.drawSegmentation(pic,queue);
System.out.format("\nSegmentation printed on top of original image and saved to %s\n",
                     segmented_filename);
pic.save(segmented_filename);

// We just paint over pic2 - this is another instance of MyPicture 
// with the same jpg file
MyPicture pic2 = new MyPicture("mando.jpg");
pic2.setOriginLowerLeft();
// We paint the leaf node segments in the queue onto this image
tree.paintSquares(pic2,queue);
System.out.format("\nPainted image computed and saved to %s\n",painted_filename);
pic2.save(painted_filename);
}

static int log2(int n)
{
return (int) (Math.log(n) / Math.log(2));
}
}