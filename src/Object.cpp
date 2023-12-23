#include "Object.hpp"

Object::Object() {
	id = generate_id();
}

Object::Object(std::vector<char>& serialized_data) {
	// id
	id = *reinterpret_cast<const ObjectId*>(serialized_data.data());
	serialized_data.erase(serialized_data.begin(), serialized_data.begin() + sizeof(ObjectId));
	// groups
	int bytes_size = serialized_data.front();
	serialized_data.erase(serialized_data.begin(), serialized_data.begin() + 1);
	for (int i = 0; i < bytes_size; i++) {
		ObjectGroup og = id = *reinterpret_cast<const ObjectGroup*>(&serialized_data[i * sizeof(ObjectGroup)]);
		groups.push_back(og);
	}
	serialized_data.erase(serialized_data.begin(), serialized_data.begin() + bytes_size * sizeof(ObjectGroup));
	// name
	bytes_size = serialized_data.front();
	name = std::string(serialized_data.begin(), serialized_data.begin() + bytes_size);
	serialized_data.erase(serialized_data.begin(), serialized_data.begin() + bytes_size);
}

std::vector<char> Object::serialize() {
	std::vector<char> v;
	const char* ptr = reinterpret_cast<const char*>(&id);
	v.insert(v.end(), ptr, ptr + sizeof(ObjectId));
	//add number of groups
	v.push_back((char)groups.size());
	for (auto& e : groups) {
		const char* group_ptr = reinterpret_cast<const char*>(&e);
		v.insert(v.end(), group_ptr, group_ptr + sizeof(ObjectGroup));
	}
	v.insert(v.end(), name.begin(), name.end());
	return v;
}