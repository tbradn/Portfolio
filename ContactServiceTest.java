package CS320MobileApplication;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

public class ContactServiceTest {

	// Test case for adding a new contact to the ContactService.
    @Test
    public void testAddContact() {
        ContactService service = new ContactService();
        Contact contact = new Contact("1234567890", "John", "Doe", "0123456789", "123 Main St");
        service.addContact(contact);
        assertEquals(contact, service.getContact("1234567890"));
    }

    // Test case for attempting to add a duplicate contact ID.
    @Test
    public void testAddDuplicateContact() {
    	ContactService service = new ContactService();
    	Contact contact1 = new Contact("1234567890", "John", "Doe", "0123456789", "123 Main St");
    	Contact contact2 = new Contact("1234567890", "Jane", "Doe", "0987654321", "321 Main St");
        service.addContact(contact1);
        assertThrows(IllegalArgumentException.class, () -> {
        	service.addContact(contact2);
        });
    }
    
    // Test case for deleting an existing contact from the ContactService.
    @Test
    public void testDeleteContact() {
        ContactService service = new ContactService();
        Contact contact = new Contact("1234567890", "John", "Doe", "0123456789", "123 Main St");
        service.addContact(contact);
        service.deleteContact("1234567890");
        assertNull(service.getContact("1234567890"));
    }
    
    // Test case for attempting to delete a contact that doesn't exist.
    @Test
    public void testDeleteNonExistingContact() {
    	ContactService service = new ContactService();
    	assertThrows(IllegalArgumentException.class, () -> {
    		service.deleteContact("12345");
    	});
    }

    // Test case for updating an existing contact's details.
    @Test
    public void testUpdateContact() {
        ContactService service = new ContactService();
        Contact contact = new Contact("1234567890", "John", "Doe", "0123456789", "123 Main St");
        service.addContact(contact);
        service.updateContact("1234567890", "Jane", "Doe", "0987654321", "456 Main St");
        Contact updatedContact = service.getContact("1234567890");
        assertEquals("Jane", updatedContact.getFirstName());
        assertEquals("Doe", updatedContact.getLastName());
        assertEquals("0987654321", updatedContact.getPhone());
        assertEquals("456 Main St", updatedContact.getAddress());
    }
    
    // Test case for attempting to update a contact the doesn't exist.
    @Test
    public void testUpdateNonExistingContact() {
    	ContactService service = new ContactService();
    	assertThrows(IllegalArgumentException.class, () -> {
    		service.updateContact("12345", "Jane", "Doe", "0987654321", "321 Main St");
    	});
    }
}
