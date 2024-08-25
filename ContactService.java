package CS320MobileApplication;

import java.util.HashMap;
import java.util.Map;

public class ContactService {
	
	// HashMap to store contacts with contactId as the key.
    private final Map<String, Contact> contacts = new HashMap<>();

    // Method to add a new contact to the service.
    public void addContact(Contact contact) {
    	
    	// Check if the contactId already exists in the map.
        if (contacts.containsKey(contact.getContactId())) {
            throw new IllegalArgumentException("Contact ID already exists");
        }
        
        // Add the contact to the map.
        contacts.put(contact.getContactId(), contact);
    }

    // Method to delete a contact by a contactId.
    public void deleteContact(String contactId) {
    	
    	// Check if the contactId exists in the map.
        if (!contacts.containsKey(contactId)) {
            throw new IllegalArgumentException("Contact ID does not exist");
        }
        
        // Remove the contact from the map.
        contacts.remove(contactId);
    }

    // Method to update an existing contact's details.
    public void updateContact(String contactId, String firstName, String lastName, String phone, String address) {
    	
    	// Retrieve the contact from the map.
        Contact contact = contacts.get(contactId);
        if (contact == null) {
            throw new IllegalArgumentException("Contact ID does not exist");
        }
        
        // Update the fields if they are not null.
        if (firstName != null) {
            contact.setFirstName(firstName);
        }
        if (lastName != null) {
            contact.setLastName(lastName);
        }
        if (phone != null) {
            contact.setPhone(phone);
        }
        if (address != null) {
            contact.setAddress(address);
        }
    }

    // Method to retrieve a contact by contactId.
    public Contact getContact(String contactId) {
        return contacts.get(contactId);
    }
}
