#pragma once

#include <string>

class Project {
  public:
	Project(int32_t createdBy);
	Project(const std::string &name, const std::string &description, int32_t createdBy);

	void setName(const std::string &name, int32_t changedBy);
	void setDescription(const std::string &description, int32_t changedBy);

	std::string getName() const;
	std::string getDescription() const;

  private:
	std::string name;
	std::string description;
	const std::string createdOn;
	const int32_t createdBy;
	std::string lastChangedOn;
	std::string lastChangedBy;

	void setName(const std::string &name);
	void setDescription(const std::string &description);

	template <typename T>
	friend void touch(T &, int32_t);
};