USE [coms-tup-db]
GO
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[WorkLogs]') AND type in (N'U'))
DROP TABLE [dbo].[WorkLogs]
GO
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[UsersTeams]') AND type in (N'U'))
DROP TABLE [dbo].[UsersTeams]
GO
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[Users]') AND type in (N'U'))
DROP TABLE [dbo].[Users]
GO
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TeamsProjects]') AND type in (N'U'))
DROP TABLE [dbo].[TeamsProjects]
GO
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[Teams]') AND type in (N'U'))
DROP TABLE [dbo].[Teams]
GO
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[Tasks]') AND type in (N'U'))
DROP TABLE [dbo].[Tasks]
GO
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[Projects]') AND type in (N'U'))
DROP TABLE [dbo].[Projects]
GO
USE [master]
GO
DROP DATABASE [coms-tup-db]
GO
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
	[IsDeleted] [bit] NOT NULL,
 CONSTRAINT [PK_Projects] PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]
GO
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
	[IsDeleted] [bit] NOT NULL,
 CONSTRAINT [PK_Tasks] PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]
GO
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
	[IsDeleted] [bit] NOT NULL,
 CONSTRAINT [PK_Teams] PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
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
	[LastChangedBy] [int] NULL,
	[AccessLevel] [tinyint] NOT NULL,
	[IsDeleted] [bit] NOT NULL,
 CONSTRAINT [PK_Users] PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
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
	[IsDeleted] [bit] NOT NULL,
 CONSTRAINT [PK_WorkLogs] PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE   VIEW [dbo].[vUsersTeams]
AS
SELECT
	u.Id AS UserId,
	u.[Username],
	u.FirstName,
	u.LastName,
	u.AccessLevel,
	u.CreatedOn AS UserCreatedOn,
	u.CreatedBy AS UserCreatedBy,
	u.LastChangedOn AS UserLastChangedOn,
	u.LastChangedBy AS UserLastChangedBy,
	u.IsDeleted AS UserIsDeleted,
	t.Id AS TeamId,
	t.[Name] AS TeamName,
	t.CreatedOn AS TeamCreatedOn,
	t.CreatedBy AS TeamCreatedBy,
	t.LastChangedOn AS TeamLastChangedOn,
	t.LastChangedBy AS TeamLastChangedBy,
	t.IsDeleted AS TeamIsDeleted
FROM Users u
INNER JOIN UsersTeams ut
ON u.Id = ut.UserId
INNER JOIN Teams t
ON t.id = ut.TeamId;
GO
SET IDENTITY_INSERT [dbo].[Projects] ON 
GO
INSERT [dbo].[Projects] ([Id], [Name], [Description], [CreatedOn], [CreatedBy], [LastChangedOn], [LastChangedBy], [IsDeleted]) VALUES (1, N'CoMS TUP', NULL, CAST(N'2021-07-11' AS Date), 1, CAST(N'2021-07-11T07:50:00.0000000' AS DateTime2), 1, 0)
GO
INSERT [dbo].[Projects] ([Id], [Name], [Description], [CreatedOn], [CreatedBy], [LastChangedOn], [LastChangedBy], [IsDeleted]) VALUES (2, N'Intsitrus', N'Portokal', CAST(N'2021-07-11' AS Date), 1, CAST(N'2021-07-11T09:34:02.0000000' AS DateTime2), 1, 0)
GO
SET IDENTITY_INSERT [dbo].[Projects] OFF
GO
SET IDENTITY_INSERT [dbo].[Tasks] ON 
GO
INSERT [dbo].[Tasks] ([Id], [ProjectId], [AssigneeId], [Title], [Description], [Status], [CreatedOn], [CreatedBy], [LastChangedOn], [LastChangedBy], [IsDeleted]) VALUES (1, 1, 1, N'Find Meaning', NULL, 1, CAST(N'2021-07-11' AS Date), 1, CAST(N'2021-07-11T08:19:33.0000000' AS DateTime2), 1, 0)
GO
SET IDENTITY_INSERT [dbo].[Tasks] OFF
GO
SET IDENTITY_INSERT [dbo].[Teams] ON 
GO
INSERT [dbo].[Teams] ([Id], [Name], [CreatedOn], [CreatedBy], [LastChangedOn], [LastChangedBy], [IsDeleted]) VALUES (1, N'CryptoTigan', CAST(N'2021-07-11' AS Date), 1, CAST(N'2021-07-11T08:34:57.0000000' AS DateTime2), 1, 0)
GO
SET IDENTITY_INSERT [dbo].[Teams] OFF
GO
SET IDENTITY_INSERT [dbo].[Users] ON 
GO
INSERT [dbo].[Users] ([Id], [Username], [Password], [FirstName], [LastName], [CreatedOn], [CreatedBy], [LastChangedOn], [LastChangedBy], [AccessLevel], [IsDeleted]) VALUES (1, N'admin', N'adminpass', N'Panelcho', N'Adminov', CAST(N'2021-07-11' AS Date), 2, CAST(N'2021-07-11T07:48:22.0000000' AS DateTime2), 2, 1, 0)
GO
INSERT [dbo].[Users] ([Id], [Username], [Password], [FirstName], [LastName], [CreatedOn], [CreatedBy], [LastChangedOn], [LastChangedBy], [AccessLevel], [IsDeleted]) VALUES (2, N'root', N'rootpass', N'The One', N'Above', CAST(N'2021-07-13' AS Date), 2, CAST(N'2021-07-13T08:22:22.0000000' AS DateTime2), 2, 2, 0)
GO
INSERT [dbo].[Users] ([Id], [Username], [Password], [FirstName], [LastName], [CreatedOn], [CreatedBy], [LastChangedOn], [LastChangedBy], [AccessLevel], [IsDeleted]) VALUES (3, N'mitko', N'not secure', N'Dimitko', N'Trimitko', CAST(N'2021-07-13' AS Date), 1, CAST(N'2021-07-14T13:28:06.0000000' AS DateTime2), 1, 0, 0)
GO
INSERT [dbo].[Users] ([Id], [Username], [Password], [FirstName], [LastName], [CreatedOn], [CreatedBy], [LastChangedOn], [LastChangedBy], [AccessLevel], [IsDeleted]) VALUES (4, N'test', N'testpass', N'Test', N'Testing', CAST(N'2021-07-14' AS Date), 1, CAST(N'2021-07-14T10:06:24.0000000' AS DateTime2), 1, 0, 1)
GO
SET IDENTITY_INSERT [dbo].[Users] OFF
GO
INSERT [dbo].[UsersTeams] ([UserId], [TeamId]) VALUES (3, 1)
GO
SET IDENTITY_INSERT [dbo].[WorkLogs] ON 
GO
INSERT [dbo].[WorkLogs] ([Id], [TaskId], [UserId], [Date], [HoursSpent], [IsDeleted]) VALUES (1, 1, 1, CAST(N'2021-07-11' AS Date), 22, 0)
GO
SET IDENTITY_INSERT [dbo].[WorkLogs] OFF
GO
ALTER TABLE [dbo].[Projects] ADD  CONSTRAINT [DF_Projects_CreatedOn]  DEFAULT (getutcdate()) FOR [CreatedOn]
GO
ALTER TABLE [dbo].[Projects] ADD  CONSTRAINT [DF_Projects_IsDeleted]  DEFAULT ((0)) FOR [IsDeleted]
GO
ALTER TABLE [dbo].[Tasks] ADD  CONSTRAINT [DF_Tasks_CreatedOn]  DEFAULT (getutcdate()) FOR [CreatedOn]
GO
ALTER TABLE [dbo].[Tasks] ADD  CONSTRAINT [DF_Tasks_IsDeleted]  DEFAULT ((0)) FOR [IsDeleted]
GO
ALTER TABLE [dbo].[Teams] ADD  CONSTRAINT [DF_Teams_CreatedOn]  DEFAULT (getutcdate()) FOR [CreatedOn]
GO
ALTER TABLE [dbo].[Teams] ADD  CONSTRAINT [DF_Teams_IsDeleted]  DEFAULT ((0)) FOR [IsDeleted]
GO
ALTER TABLE [dbo].[Users] ADD  CONSTRAINT [DF_Users_CreatedOn]  DEFAULT (getutcdate()) FOR [CreatedOn]
GO
ALTER TABLE [dbo].[Users] ADD  CONSTRAINT [DF_Users_IsAdmin]  DEFAULT ((0)) FOR [AccessLevel]
GO
ALTER TABLE [dbo].[Users] ADD  CONSTRAINT [DF_Users_IsDeleted]  DEFAULT ((0)) FOR [IsDeleted]
GO
ALTER TABLE [dbo].[WorkLogs] ADD  CONSTRAINT [DF_WorkLogs_IsDeleted]  DEFAULT ((0)) FOR [IsDeleted]
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
