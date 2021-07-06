USE [coms-tup-db]
GO
ALTER TABLE [dbo].[Tasks] DROP CONSTRAINT [CK_Tasks_Status]
GO
ALTER TABLE [dbo].[WorkLogs] DROP CONSTRAINT [FK_WorkLogs_Users]
GO
ALTER TABLE [dbo].[WorkLogs] DROP CONSTRAINT [FK_WorkLogs_Tasks]
GO
ALTER TABLE [dbo].[UsersTeams] DROP CONSTRAINT [FK_UsersTeams_Users]
GO
ALTER TABLE [dbo].[UsersTeams] DROP CONSTRAINT [FK_UsersTeams_Teams]
GO
ALTER TABLE [dbo].[Users] DROP CONSTRAINT [FK_Users-LastChangedBy_Users]
GO
ALTER TABLE [dbo].[Users] DROP CONSTRAINT [FK_Users-CreatedBy_Users]
GO
ALTER TABLE [dbo].[TeamsProjects] DROP CONSTRAINT [FK_TeamsProjects_Teams]
GO
ALTER TABLE [dbo].[TeamsProjects] DROP CONSTRAINT [FK_TeamsProjects_Projects]
GO
ALTER TABLE [dbo].[Teams] DROP CONSTRAINT [FK_Teams-LastChangedBy_Users]
GO
ALTER TABLE [dbo].[Teams] DROP CONSTRAINT [FK_Teams-CreatedBy_Users]
GO
ALTER TABLE [dbo].[Tasks] DROP CONSTRAINT [FK_Tasks-LastChangedBy_Users]
GO
ALTER TABLE [dbo].[Tasks] DROP CONSTRAINT [FK_Tasks-CreatedBy_Users]
GO
ALTER TABLE [dbo].[Tasks] DROP CONSTRAINT [FK_Tasks-AssigneeId_Users]
GO
ALTER TABLE [dbo].[Tasks] DROP CONSTRAINT [FK_Tasks_Projects]
GO
ALTER TABLE [dbo].[Projects] DROP CONSTRAINT [FK_Projects-LastChangedBy_Users]
GO
ALTER TABLE [dbo].[Projects] DROP CONSTRAINT [FK_Projects-CreatedBy_Users]
GO
ALTER TABLE [dbo].[Users] DROP CONSTRAINT [DF_Users_IsAdmin]
GO
ALTER TABLE [dbo].[Users] DROP CONSTRAINT [DF_Users_CreatedOn]
GO
ALTER TABLE [dbo].[Teams] DROP CONSTRAINT [DF_Teams_CreatedOn]
GO
ALTER TABLE [dbo].[Tasks] DROP CONSTRAINT [DF_Tasks_CreatedOn]
GO
ALTER TABLE [dbo].[Projects] DROP CONSTRAINT [DF_Projects_CreatedOn]
GO
/****** Object:  Table [dbo].[WorkLogs]    Script Date: 7/6/2021 9:29:41 AM ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[WorkLogs]') AND type in (N'U'))
DROP TABLE [dbo].[WorkLogs]
GO
/****** Object:  Table [dbo].[UsersTeams]    Script Date: 7/6/2021 9:29:41 AM ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[UsersTeams]') AND type in (N'U'))
DROP TABLE [dbo].[UsersTeams]
GO
/****** Object:  Table [dbo].[Users]    Script Date: 7/6/2021 9:29:41 AM ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[Users]') AND type in (N'U'))
DROP TABLE [dbo].[Users]
GO
/****** Object:  Table [dbo].[TeamsProjects]    Script Date: 7/6/2021 9:29:41 AM ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TeamsProjects]') AND type in (N'U'))
DROP TABLE [dbo].[TeamsProjects]
GO
/****** Object:  Table [dbo].[Teams]    Script Date: 7/6/2021 9:29:41 AM ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[Teams]') AND type in (N'U'))
DROP TABLE [dbo].[Teams]
GO
/****** Object:  Table [dbo].[Tasks]    Script Date: 7/6/2021 9:29:41 AM ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[Tasks]') AND type in (N'U'))
DROP TABLE [dbo].[Tasks]
GO
/****** Object:  Table [dbo].[Projects]    Script Date: 7/6/2021 9:29:41 AM ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[Projects]') AND type in (N'U'))
DROP TABLE [dbo].[Projects]
GO
USE [master]
GO
/****** Object:  Database [coms-tup-db]    Script Date: 7/6/2021 9:29:41 AM ******/
DROP DATABASE [coms-tup-db]
GO
/****** Object:  Database [coms-tup-db]    Script Date: 7/6/2021 9:29:41 AM ******/
CREATE DATABASE [coms-tup-db]
 CONTAINMENT = NONE
 ON  PRIMARY 
( NAME = N'coms-tup-db', FILENAME = N'<PRFX>\coms-tup-db.mdf' , SIZE = 8192KB , MAXSIZE = UNLIMITED, FILEGROWTH = 65536KB )
 LOG ON 
( NAME = N'coms-tup-db_log', FILENAME = N'<PRFX>\coms-tup-db_log.ldf' , SIZE = 8192KB , MAXSIZE = 2048GB , FILEGROWTH = 65536KB )
GO
IF (1 = FULLTEXTSERVICEPROPERTY('IsFullTextInstalled'))
begin
EXEC [coms-tup-db].[dbo].[sp_fulltext_database] @action = 'enable'
end
GO
ALTER DATABASE [coms-tup-db] SET ANSI_NULL_DEFAULT OFF 
GO
ALTER DATABASE [coms-tup-db] SET ANSI_NULLS OFF 
GO
ALTER DATABASE [coms-tup-db] SET ANSI_PADDING OFF 
GO
ALTER DATABASE [coms-tup-db] SET ANSI_WARNINGS OFF 
GO
ALTER DATABASE [coms-tup-db] SET ARITHABORT OFF 
GO
ALTER DATABASE [coms-tup-db] SET AUTO_CLOSE OFF 
GO
ALTER DATABASE [coms-tup-db] SET AUTO_SHRINK OFF 
GO
ALTER DATABASE [coms-tup-db] SET AUTO_UPDATE_STATISTICS ON 
GO
ALTER DATABASE [coms-tup-db] SET CURSOR_CLOSE_ON_COMMIT OFF 
GO
ALTER DATABASE [coms-tup-db] SET CURSOR_DEFAULT  GLOBAL 
GO
ALTER DATABASE [coms-tup-db] SET CONCAT_NULL_YIELDS_NULL OFF 
GO
ALTER DATABASE [coms-tup-db] SET NUMERIC_ROUNDABORT OFF 
GO
ALTER DATABASE [coms-tup-db] SET QUOTED_IDENTIFIER OFF 
GO
ALTER DATABASE [coms-tup-db] SET RECURSIVE_TRIGGERS OFF 
GO
ALTER DATABASE [coms-tup-db] SET  DISABLE_BROKER 
GO
ALTER DATABASE [coms-tup-db] SET AUTO_UPDATE_STATISTICS_ASYNC OFF 
GO
ALTER DATABASE [coms-tup-db] SET DATE_CORRELATION_OPTIMIZATION OFF 
GO
ALTER DATABASE [coms-tup-db] SET TRUSTWORTHY OFF 
GO
ALTER DATABASE [coms-tup-db] SET ALLOW_SNAPSHOT_ISOLATION OFF 
GO
ALTER DATABASE [coms-tup-db] SET PARAMETERIZATION SIMPLE 
GO
ALTER DATABASE [coms-tup-db] SET READ_COMMITTED_SNAPSHOT OFF 
GO
ALTER DATABASE [coms-tup-db] SET HONOR_BROKER_PRIORITY OFF 
GO
ALTER DATABASE [coms-tup-db] SET RECOVERY SIMPLE 
GO
ALTER DATABASE [coms-tup-db] SET  MULTI_USER 
GO
ALTER DATABASE [coms-tup-db] SET PAGE_VERIFY CHECKSUM  
GO
ALTER DATABASE [coms-tup-db] SET DB_CHAINING OFF 
GO
ALTER DATABASE [coms-tup-db] SET FILESTREAM( NON_TRANSACTED_ACCESS = OFF ) 
GO
ALTER DATABASE [coms-tup-db] SET TARGET_RECOVERY_TIME = 60 SECONDS 
GO
ALTER DATABASE [coms-tup-db] SET DELAYED_DURABILITY = DISABLED 
GO
USE [coms-tup-db]
GO
/****** Object:  Table [dbo].[Projects]    Script Date: 7/6/2021 9:29:41 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Projects](
	[Id] [int] IDENTITY(1,1) NOT NULL,
	[Name] [nvarchar](50) NOT NULL,
	[Description] [nvarchar](max) NULL,
	[CreatedOn] [date] NOT NULL,
	[CreatedBy] [int] NOT NULL,
	[LastChangedOn] [datetime2](0) NOT NULL,
	[LastChangedBy] [int] NOT NULL,
 CONSTRAINT [PK_Projects] PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]
GO
/****** Object:  Table [dbo].[Tasks]    Script Date: 7/6/2021 9:29:41 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Tasks](
	[Id] [int] IDENTITY(1,1) NOT NULL,
	[ProjectId] [int] NOT NULL,
	[AssigneeId] [int] NOT NULL,
	[Title] [nvarchar](50) NOT NULL,
	[Description] [nvarchar](max) NULL,
	[Status] [tinyint] NOT NULL,
	[CreatedOn] [date] NOT NULL,
	[CreatedBy] [int] NOT NULL,
	[LastChangedOn] [datetime2](0) NOT NULL,
	[LastChangedBy] [int] NOT NULL,
 CONSTRAINT [PK_Tasks] PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]
GO
/****** Object:  Table [dbo].[Teams]    Script Date: 7/6/2021 9:29:41 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Teams](
	[Id] [int] IDENTITY(1,1) NOT NULL,
	[Name] [nvarchar](50) NOT NULL,
	[CreatedOn] [date] NOT NULL,
	[CreatedBy] [int] NOT NULL,
	[LastChangedOn] [datetime2](0) NOT NULL,
	[LastChangedBy] [int] NOT NULL,
 CONSTRAINT [PK_Teams] PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[TeamsProjects]    Script Date: 7/6/2021 9:29:41 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TeamsProjects](
	[TeamId] [int] NOT NULL,
	[ProjectId] [int] NOT NULL,
 CONSTRAINT [PK_TeamsProjects] PRIMARY KEY CLUSTERED 
(
	[TeamId] ASC,
	[ProjectId] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[Users]    Script Date: 7/6/2021 9:29:41 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Users](
	[Id] [int] IDENTITY(1,1) NOT NULL,
	[Username] [varchar](50) NOT NULL,
	[Password] [varchar](50) NOT NULL,
	[FirstName] [nvarchar](50) NOT NULL,
	[LastName] [nvarchar](50) NOT NULL,
	[CreatedOn] [date] NOT NULL,
	[CreatedBy] [int] NULL,
	[LastChangedOn] [datetime2](0) NOT NULL,
	[LastChangedBy] [int] NOT NULL,
	[IsAdmin] [bit] NOT NULL,
 CONSTRAINT [PK_Users] PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[UsersTeams]    Script Date: 7/6/2021 9:29:41 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[UsersTeams](
	[UserId] [int] NOT NULL,
	[TeamId] [int] NOT NULL,
 CONSTRAINT [PK_UsersTeams] PRIMARY KEY CLUSTERED 
(
	[UserId] ASC,
	[TeamId] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[WorkLogs]    Script Date: 7/6/2021 9:29:41 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[WorkLogs](
	[Id] [int] IDENTITY(1,1) NOT NULL,
	[TaskId] [int] NOT NULL,
	[UserId] [int] NOT NULL,
	[Date] [date] NOT NULL,
	[HoursSpent] [tinyint] NOT NULL,
 CONSTRAINT [PK_WorkLogs] PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
ALTER TABLE [dbo].[Projects] ADD  CONSTRAINT [DF_Projects_CreatedOn]  DEFAULT (getutcdate()) FOR [CreatedOn]
GO
ALTER TABLE [dbo].[Tasks] ADD  CONSTRAINT [DF_Tasks_CreatedOn]  DEFAULT (getutcdate()) FOR [CreatedOn]
GO
ALTER TABLE [dbo].[Teams] ADD  CONSTRAINT [DF_Teams_CreatedOn]  DEFAULT (getutcdate()) FOR [CreatedOn]
GO
ALTER TABLE [dbo].[Users] ADD  CONSTRAINT [DF_Users_CreatedOn]  DEFAULT (getutcdate()) FOR [CreatedOn]
GO
ALTER TABLE [dbo].[Users] ADD  CONSTRAINT [DF_Users_IsAdmin]  DEFAULT ((0)) FOR [IsAdmin]
GO
ALTER TABLE [dbo].[Projects]  WITH CHECK ADD  CONSTRAINT [FK_Projects-CreatedBy_Users] FOREIGN KEY([CreatedBy])
REFERENCES [dbo].[Users] ([Id])
GO
ALTER TABLE [dbo].[Projects] CHECK CONSTRAINT [FK_Projects-CreatedBy_Users]
GO
ALTER TABLE [dbo].[Projects]  WITH CHECK ADD  CONSTRAINT [FK_Projects-LastChangedBy_Users] FOREIGN KEY([LastChangedBy])
REFERENCES [dbo].[Users] ([Id])
GO
ALTER TABLE [dbo].[Projects] CHECK CONSTRAINT [FK_Projects-LastChangedBy_Users]
GO
ALTER TABLE [dbo].[Tasks]  WITH CHECK ADD  CONSTRAINT [FK_Tasks_Projects] FOREIGN KEY([ProjectId])
REFERENCES [dbo].[Projects] ([Id])
GO
ALTER TABLE [dbo].[Tasks] CHECK CONSTRAINT [FK_Tasks_Projects]
GO
ALTER TABLE [dbo].[Tasks]  WITH CHECK ADD  CONSTRAINT [FK_Tasks-AssigneeId_Users] FOREIGN KEY([AssigneeId])
REFERENCES [dbo].[Users] ([Id])
GO
ALTER TABLE [dbo].[Tasks] CHECK CONSTRAINT [FK_Tasks-AssigneeId_Users]
GO
ALTER TABLE [dbo].[Tasks]  WITH CHECK ADD  CONSTRAINT [FK_Tasks-CreatedBy_Users] FOREIGN KEY([CreatedBy])
REFERENCES [dbo].[Users] ([Id])
GO
ALTER TABLE [dbo].[Tasks] CHECK CONSTRAINT [FK_Tasks-CreatedBy_Users]
GO
ALTER TABLE [dbo].[Tasks]  WITH CHECK ADD  CONSTRAINT [FK_Tasks-LastChangedBy_Users] FOREIGN KEY([LastChangedBy])
REFERENCES [dbo].[Users] ([Id])
GO
ALTER TABLE [dbo].[Tasks] CHECK CONSTRAINT [FK_Tasks-LastChangedBy_Users]
GO
ALTER TABLE [dbo].[Teams]  WITH CHECK ADD  CONSTRAINT [FK_Teams-CreatedBy_Users] FOREIGN KEY([CreatedBy])
REFERENCES [dbo].[Users] ([Id])
GO
ALTER TABLE [dbo].[Teams] CHECK CONSTRAINT [FK_Teams-CreatedBy_Users]
GO
ALTER TABLE [dbo].[Teams]  WITH CHECK ADD  CONSTRAINT [FK_Teams-LastChangedBy_Users] FOREIGN KEY([LastChangedBy])
REFERENCES [dbo].[Users] ([Id])
GO
ALTER TABLE [dbo].[Teams] CHECK CONSTRAINT [FK_Teams-LastChangedBy_Users]
GO
ALTER TABLE [dbo].[TeamsProjects]  WITH CHECK ADD  CONSTRAINT [FK_TeamsProjects_Projects] FOREIGN KEY([ProjectId])
REFERENCES [dbo].[Projects] ([Id])
GO
ALTER TABLE [dbo].[TeamsProjects] CHECK CONSTRAINT [FK_TeamsProjects_Projects]
GO
ALTER TABLE [dbo].[TeamsProjects]  WITH CHECK ADD  CONSTRAINT [FK_TeamsProjects_Teams] FOREIGN KEY([TeamId])
REFERENCES [dbo].[Teams] ([Id])
GO
ALTER TABLE [dbo].[TeamsProjects] CHECK CONSTRAINT [FK_TeamsProjects_Teams]
GO
ALTER TABLE [dbo].[Users]  WITH CHECK ADD  CONSTRAINT [FK_Users-CreatedBy_Users] FOREIGN KEY([CreatedBy])
REFERENCES [dbo].[Users] ([Id])
GO
ALTER TABLE [dbo].[Users] CHECK CONSTRAINT [FK_Users-CreatedBy_Users]
GO
ALTER TABLE [dbo].[Users]  WITH CHECK ADD  CONSTRAINT [FK_Users-LastChangedBy_Users] FOREIGN KEY([LastChangedBy])
REFERENCES [dbo].[Users] ([Id])
GO
ALTER TABLE [dbo].[Users] CHECK CONSTRAINT [FK_Users-LastChangedBy_Users]
GO
ALTER TABLE [dbo].[UsersTeams]  WITH CHECK ADD  CONSTRAINT [FK_UsersTeams_Teams] FOREIGN KEY([TeamId])
REFERENCES [dbo].[Teams] ([Id])
GO
ALTER TABLE [dbo].[UsersTeams] CHECK CONSTRAINT [FK_UsersTeams_Teams]
GO
ALTER TABLE [dbo].[UsersTeams]  WITH CHECK ADD  CONSTRAINT [FK_UsersTeams_Users] FOREIGN KEY([UserId])
REFERENCES [dbo].[Users] ([Id])
GO
ALTER TABLE [dbo].[UsersTeams] CHECK CONSTRAINT [FK_UsersTeams_Users]
GO
ALTER TABLE [dbo].[WorkLogs]  WITH CHECK ADD  CONSTRAINT [FK_WorkLogs_Tasks] FOREIGN KEY([TaskId])
REFERENCES [dbo].[Tasks] ([Id])
GO
ALTER TABLE [dbo].[WorkLogs] CHECK CONSTRAINT [FK_WorkLogs_Tasks]
GO
ALTER TABLE [dbo].[WorkLogs]  WITH CHECK ADD  CONSTRAINT [FK_WorkLogs_Users] FOREIGN KEY([UserId])
REFERENCES [dbo].[Users] ([Id])
GO
ALTER TABLE [dbo].[WorkLogs] CHECK CONSTRAINT [FK_WorkLogs_Users]
GO
ALTER TABLE [dbo].[Tasks]  WITH CHECK ADD  CONSTRAINT [CK_Tasks_Status] CHECK  (([Status]>=(0) AND [Status]<=(3)))
GO
ALTER TABLE [dbo].[Tasks] CHECK CONSTRAINT [CK_Tasks_Status]
GO
USE [master]
GO
ALTER DATABASE [coms-tup-db] SET  READ_WRITE 
GO
