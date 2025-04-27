#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun Mar 30 18:12:47 2025

@author: tristenbradne_snhu
"""

from pymongo import MongoClient
from bson.objectid import ObjectId
import json

class AnimalShelter(object):
    """ CRUD operations for Animal collection in MongoDB """

    def __init__(self, username, password, host='nv-desktop-services.apporto.com', port=30325, db='AAC', collection='animals'):
        """
        Initializes the AnimalShelter object with a connection to MongoDB
        
        Args:
            username (str): MongoDB username
            password (str): MongoDB password
            host (str): MongoDB host
            port (int): MongoDB port
            db (str): Database name
            collection (str): Collection name
        """
        # Initialize MongoClient
        self.client = MongoClient(f'mongodb://{username}:{password}@{host}:{port}/{db}')
        
        # Connect to the database
        self.database = self.client[db]
        
        # Set the collection
        self.collection = collection

    def create(self, data):
        """
        Creates a document in the animals collection
        
        Args:
            data (dict): Data to be inserted as a document
            
        Returns:
            bool: True if successful, False otherwise
        """
        if data is not None:
            try:
                self.database[self.collection].insert_one(data)  # data should be dictionary
                return True
            except Exception as e:
                print(f"An error occurred while creating: {e}")
                return False
        else:
            raise Exception("Nothing to save, because data parameter is empty")
            return False

    def read(self, criteria=None, projection=None):
        """
        Reads documents from the animals collection
        
        Args:
            criteria (dict): Search criteria
            projection (dict): Fields to include or exclude
            
        Returns:
            list: List of dictionaries containing documents that match the criteria
        """
        if criteria is None:
            criteria = {}
            
        try:
            # If projection is provided, use it; otherwise, return all fields
            if projection:
                data = list(self.database[self.collection].find(criteria, projection))
            else:
                data = list(self.database[self.collection].find(criteria))
                
            # Convert ObjectId to string for JSON serialization
            for document in data:
                if '_id' in document:
                    document['_id'] = str(document['_id'])
            return data
        except Exception as e:
            print(f"An error occurred while reading: {e}")
            return []

    def update(self, criteria, update_data):
        """
        Updates documents in the animals collection
        
        Args:
            criteria (dict): Search criteria
            update_data (dict): Data to update
            
        Returns:
            int: Number of documents updated
        """
        if criteria is None or update_data is None:
            raise Exception("Both criteria and update_data must be provided")
            return 0
            
        try:
            result = self.database[self.collection].update_many(criteria, {"$set": update_data})
            return result.modified_count
        except Exception as e:
            print(f"An error occurred while updating: {e}")
            return 0

    def delete(self, criteria):
        """
        Deletes documents from the animals collection
        
        Args:
            criteria (dict): Search criteria
            
        Returns:
            int: Number of documents deleted
        """
        if criteria is None:
            raise Exception("Criteria must be provided")
            return 0
            
        try:
            result = self.database[self.collection].delete_many(criteria)
            return result.deleted_count
        except Exception as e:
            print(f"An error occurred while deleting: {e}")
            return 0