#pragma once

#include <map>
#include <nanodbc.h>

class DBManager;

#include "Project.h"
#include "Task.h"
#include "Team.h"
#include "User.h"
#include "WorkLog.h"

/**
 * @file DBManager.h
 *
 * @brief Declaration of the DBManager class
 */

/**
 * @brief The DBManager class is responsible for all interactions between the application and the database.
 *
 * It acts as a wrapper for #connection, providing member functions with all queries needed by the program.
 */

class DBManager {
  public:
	/**
	 * @brief The default constructor.
	 *
	 * @note This constructor is currently of no use.
	 */
	DBManager() = default;
	/**
	 * @brief Connection string constructor.
	 *
	 * Initilises the internal nanodbc conection with the specified connection string.
	 *
	 * @param connectionString The connection string to pass.
	 */
	DBManager(const std::string &connectionString);
	/**
	 * @brief Parametarised constructor.
	 *
	 * Generates a connection string using the given parameters and uses it to intialise the internal nanodbc
	 * connection. Assumes you are using "Trusted_Connection=yes;"
	 *
	 * @param driver The value after "Driver="
	 * @param server The value after "Server="
	 * @param database The value after "Database="
	 */
	DBManager(const std::string &driver, const std::string &server, const std::string &database);

	/**
	 * @brief Inserts given project into the database.
	 *
	 * @note Does not honour the project's id member.
	 *
	 * @param project The project to insert.
	 *
	 * @return True if the operation was successful, false otherwise.
	 */
	bool insert(const Project &project);
	/**
	 * @brief Inserts given task into the database.
	 *
	 * @note Does not honour the task's id member.
	 *
	 * @param task The task to insert.
	 *
	 * @return True if the operation was successful, false otherwise.
	 */
	bool insert(const Task &task);
	/**
	 * @brief Inserts given team into the database.
	 *
	 * @note Does not honour the team's id member.
	 *
	 * @param team The team to insert.
	 *
	 * @return True if the operation was successful, false otherwise.
	 */
	bool insert(const Team &team);
	/**
	 * @brief Inserts given user into the database.
	 *
	 * @note Does not honour the user's id member.
	 *
	 * @param user The user to insert.
	 * @param password The password with which to save the user.
	 *
	 * @return True if the operation was successful, false otherwise.
	 */
	bool insert(const User &user, const std::string &password);
	/**
	 * @brief Inserts given work log into the database.
	 *
	 * @note Does not honour the work log's id member.
	 *
	 * @param workLog The work log to insert.
	 *
	 * @return True if the operation was successful, false otherwise.
	 */
	bool insert(const WorkLog &workLog);

	/**
	 * @brief Updates the database entry for the given project.
	 *
	 * @note Determines which entry to update using the value returned by Project::getID().
	 *
	 * @param project The project to update.
	 *
	 * @return True if the operation was successful, false otherwise.
	 */
	bool updateByID(const Project &project);
	/**
	 * @brief Updates the database entry for the given task.
	 *
	 * @note Determines which entry to update using the value returned by Task::getID().
	 *
	 * @param task The task to update.
	 *
	 * @return True if the operation was successful, false otherwise.
	 */
	bool updateByID(const Task &task);
	/**
	 * @brief Updates the database entry for the given team.
	 *
	 * @note Determines which entry to update using the value returned by Team::getID().
	 *
	 * @param team The team to update.
	 *
	 * @return True if the operation was successful, false otherwise.
	 */
	bool updateByID(const Team &team);
	/**
	 * @brief Updates the database entry for the given user.
	 *
	 * @note Determines which entry to update using the value returned by User::getID().
	 *
	 * @param user The user to update.
	 *
	 * @return True if the operation was successful, false otherwise.
	 */
	bool updateByID(const User &user);
	/**
	 * @brief Updates the database entry for the given user.
	 *
	 * @note Determines which entry to update using the value returned by User::getID().
	 *
	 * @param user The user to update.
	 * @param password The new password to be saved.
	 *
	 * @return True if the operation was successful, false otherwise.
	 */
	bool updateByID(const User &user, const std::string &password);

	/**
	 * @brief Deletes the database entry for the given project.
	 *
	 * @note Determines which entry to delete using the value returned by Project::getID().
	 *
	 * @param project The project to delete.
	 *
	 * @return True if the operation was successful, false otherwise.
	 */
	bool deleteByID(const Project &project);
	/**
	 * @brief Deletes the database entry for the given task.
	 *
	 * @note Determines which entry to delete using the value returned by Task::getID().
	 *
	 * @param task The task to delete.
	 *
	 * @return True if the operation was successful, false otherwise.
	 */
	bool deleteByID(const Task &task);
	/**
	 * @brief Deletes the database entry for the given team.
	 *
	 * @note Determines which entry to delete using the value returned by Team::getID().
	 *
	 * @param team The team to delete.
	 *
	 * @return True if the operation was successful, false otherwise.
	 */
	bool deleteByID(const Team &team);
	/**
	 * @brief Deletes the database entry for the given user.
	 *
	 * @note Determines which entry to delete using the value returned by User::getID().
	 *
	 * @param user The user to delete.
	 *
	 * @return True if the operation was successful, false otherwise.
	 */
	bool deleteByID(const User &user);
	/**
	 * @brief Deletes the database entry for the given work log.
	 *
	 * @note Determines which entry to delete using the value returned by WorkLog::getID().
	 *
	 * @param workLog The work log to delete.
	 *
	 * @return True if the operation was successful, false otherwise.
	 */
	bool deleteByID(const WorkLog &workLog);

	/**
	 * @brief Adds an entry linking a user to a team
	 *
	 * @param team The team to which the user is to be assigned.
	 * @param user The user to assign.
	 *
	 * @return True if the operation was successful, false otherwise.
	 */
	bool assignTeamMember(const Team &team, const User &user);
	/**
	 * @brief Delets the entry linking a user to a team
	 *
	 * @param team The team from which the user is to be dismissed.
	 * @param user The user to dismiss.
	 *
	 * @return True if the operation was successful, false otherwise.
	 */
	bool dismissTeamMember(const Team &team, const User &user);

	/**
	 * @brief Adds an entry linking a team to a project
	 *
	 * @param project The project to which the team is to be assigned.
	 * @param team The team to assign.
	 *
	 * @return True if the operation was successful, false otherwise.
	 */
	bool assignTeam(const Project &project, const Team &team);
	/**
	 * @brief Delets the entry linking a team to a project
	 *
	 * @param project The project from which the team is to be dismissed.
	 * @param team The team to dismiss.
	 *
	 * @return True if the operation was successful, false otherwise.
	 */
	bool dismissTeam(const Project &project, const Team &team);

	/**
	 * @brief Returns the project with the corresponding ID from the database.
	 *
	 * @param project This parameter is used for overload resolution and as a fallback if the database operation is
	 * unsuccessful.
	 * @param id The ID of the wanted project.
	 *
	 * @return The found project or @p project if the operation fails.
	 */
	Project getByID(Project &project, int32_t id);
	/**
	 * @brief Returns the task with the corresponding ID from the database.
	 *
	 * @param task This parameter is used for overload resolution and as a fallback if the database operation is
	 * unsuccessful.
	 * @param id The ID of the wanted task.
	 *
	 * @return The found task or @p task if the operation fails.
	 */
	Task getByID(Task &task, int32_t id);
	/**
	 * @brief Returns the team with the corresponding ID from the database.
	 *
	 * @param team This parameter is used for overload resolution and as a fallback if the database operation is
	 * unsuccessful.
	 * @param id The ID of the wanted team.
	 *
	 * @return The found team or @p team if the operation fails.
	 */
	Team getByID(Team &team, int32_t id);
	/**
	 * @brief Returns the user with the corresponding ID from the database.
	 *
	 * @param user This parameter is used for overload resolution and as a fallback if the database operation is
	 * unsuccessful.
	 * @param id The ID of the wanted user.
	 *
	 * @return The found user or @p user if the operation fails.
	 */
	User getByID(User &user, int32_t id);
	/**
	 * @brief Returns the work log with the corresponding ID from the database.
	 *
	 * @param workLog This parameter is used for overload resolution and as a fallback if the database operation is
	 * unsuccessful.
	 * @param id The ID of the wanted work log.
	 *
	 * @return The found work log or @p work log if the operation fails.
	 */
	WorkLog getByID(WorkLog &workLog, int32_t id);

	/**
	 * @brief Returns all projects in the database
	 *
	 * @return A std::map with the IDs as keys and the projects as values.
	 */
	std::map<int32_t, Project> getAllProjects();
	/**
	 * @brief Returns all teams in the database
	 *
	 * @return A std::map with the IDs as keys and the teams as values.
	 */
	std::map<int32_t, Team> getAllTeams();
	/**
	 * @brief Returns all users in the database
	 *
	 * @return A std::map with the IDs as keys and the projects as values.
	 */
	std::map<int32_t, User> getAllUsers();

	/**
	 * @brief Returns all users who are members of the given team.
	 *
	 * @param team The team whose members to find.
	 *
	 * @return A std::map with the IDs as keys and the users as values.
	 */
	std::map<int32_t, User> getMembersOfTeam(const Team &team);

	/**
	 * @brief Returns all projects assigned to the given user.
	 *
	 * @param user The user whose projects to find.
	 *
	 * @return A std::map with the IDs as keys and the projects as values.
	 */
	std::map<int32_t, Project> getProjectsAssignedToUser(const User &user);
	/**
	 * @brief Returns all teams assigned to the given project.
	 *
	 * @param project The project whose teams to find.
	 *
	 * @return A std::map with the IDs as keys and the teams as values.
	 */
	std::map<int32_t, Team> getAssignedTeams(const Project &project);

	/**
	 * @brief Finds the ID of the user with matching username and password.
	 *
	 * @param username The username to look for.
	 * @param password The password to match.
	 *
	 * @return The wanted ID if it is found.
	 *
	 * @exception std::runtime_error No user with matching username and password exists.
	 */
	int32_t getIDWithCredentials(const std::string &username, const std::string &password);

	/**
	 * @brief Gets the current date from the database.
	 *
	 * @note The time is in UTC and does not include timezone information.
	 * @note The output's @c fract field is set to 0.
	 *
	 * @param includeTime If set to false, the @c hour, @c min and @c sec fields are set to 0.
	 *
	 * @return A nanodbc::timestamp containing the requested date.
	 */
	nanodbc::timestamp getDate(bool includeTime = false);

  private:
	/**
	 * The connection on which all queries are executed.
	 */
	nanodbc::connection connection;
};
