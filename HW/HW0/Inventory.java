/**
 * Inventory class
 * Interacts with: Item, Main
 */
public class Inventory {
	//declare vars
	private Item[] inventory;
	private int[] stock;
	private int numItems;
	private static int maxInventorySize;

	Inventory(int maxInventorySize) {

	}

	public int addItem(Item it, int count) {
		if (numItems >= maxInventorySize) {
			System.out.println("Cannot add another item to the Inventory: Maximum number of items reached.")
			return -1 //early return an error

			if (count <= 0)
			//set the item’s stock count in the stock array to 0
		}
		else {
			//set it the count passed in
		}

	}

	public int soldItem(int id) {
		for (i=0; i < numItems; i++) {
			Item it = inventory[i]
			if (it.getID() == id) {
				if (stock[id] < 1)
					System.out.println("Could not sell item: Item's inventory count is 0.")
				return -1
				stock[id]--
				System.out.println("Sold Item and inventory stock decremented")
			}
		}
		System.out.println("Could not sell item: not in inventory")

	}

	public void printInventory() {
		System.out.println("Store has the following items in the inventory:")
		for (i=0; i < numItems; i++) {
			Item it = inventory[i]
			it.print()
			System.out.print(" " + stock[it.getID()])
			//todo lots more
		}

	}


}