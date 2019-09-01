/**
 * Inventory class
 * Interacts with: Item, Main
 * CS 305, Fall 2019
 * @author Kai Richardson
 * @version September 2019
 */
public class Inventory {
	//declare vars
	private Item[] inventory;
	private int[] stock;
	private int numItems;
	private static int maxInventorySize;

	Inventory(int maxinv) {
		//Default size of 10 for maxInvSize if not specified.
		if (maxinv > 0) maxInventorySize = maxinv;
		else maxInventorySize = 10;
		inventory = new Item[maxInventorySize];
		stock = new int[maxInventorySize];
		numItems = 0;
	}

	public int addItem(Item it, int count) {
		if (numItems >= maxInventorySize--) {
			System.out.println("Cannot add another item to the Inventory: Maximum number of items reached.");
			return -1;
		}

		//Add our new item to inventory[]
		inventory[numItems] = it;

		//update stock[] accordingly
		if (count < 0) {
			stock[numItems] = 0;
		}

		else {
			stock[numItems] = count;
		}

		//increment numItems so we know how far to search
		numItems++;
		return 1;
	}

	public int soldItem(int id) {
		for (int i=0; i < numItems; i++) {
			Item it = inventory[i];
			if (it.getID() == id) { //only use it if the id matches
				if (stock[i] < 1) {
					System.out.println("Could not sell item: Item's inventory count is 0.");
					return -1;
				}

				stock[i]--;
				System.out.println("Sold Item and inventory stock decremented");
				return 1;
			}
		}
		System.out.println("Could not sell item: not in inventory");
		return -1;
	}

	public void printInventory() {
		double calcvalue = 0;
		double mincost = Double.MAX_VALUE; //extremely high number
		double maxcost = 0;
		System.out.println("Store has the following items in the inventory:");
		System.out.println("Item" + " price" + "\t" + "name" + "\t" + "\t" + "id" + "\t" + "stock");
		for (int i=0; i < numItems; i++) {
			Item it = inventory[i];
			it.print();
			System.out.println("\t" + stock[i]);

			double cost = it.getPrice();

			//add to total calculated 'value' of the whole Inventory
			calcvalue += cost * stock[i];

			if (cost < mincost) mincost = cost;
			if (cost > maxcost) maxcost = cost;
		}
		System.out.println("The total inventory is worth: " + calcvalue);
		System.out.println("The cheapest item store carries is: " + mincost);
		System.out.println("The most expensive item store carries is: " + maxcost);

	}


}