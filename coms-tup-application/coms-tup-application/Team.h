#pragma once

#include <string>
#include <unordered_set>

class Team {
  public:
	Team(int32_t createdBy);
	Team(const std::string &name, int32_t createdBy);

	void setName(const std::string &name, int32_t changedBy);

	std::string getName() const;

  private:
	std::string name;
	const std::string createdOn;
	const int32_t createdBy;
	std::string lastChangedOn;
	int32_t lastChangedBy;

	std::unordered_set<int32_t> memberIDs;

	void setName(const std::string &name);

	template <typename T>
	friend void touch(T &, int32_t);
};