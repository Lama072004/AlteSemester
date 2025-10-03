DROP TABLE IF EXISTS Enrollment;
DROP TABLE IF EXISTS Offering;
DROP TABLE IF EXISTS Student;
DROP TABLE IF EXISTS Course;
DROP TABLE IF EXISTS Faculty;



/*-------------------- Student --------------------------------*/

CREATE TABLE Student (
stdNo char(11) not null,
stdFirstName varchar(30) not null,
stdLastName varchar(30) not null,
stdCity varchar(30) not null,
stdState char(2) not null,
stdZip char(10) not null,
stdMajor char(6),
stdClass char(2),
stdGPA decimal(3,2),
CONSTRAINT StudentPk PRIMARY KEY (StdNo) );


/*-------------------- Course --------------------------------*/

CREATE TABLE Course(
courseNo char(6) not null,
crsDesc  varchar(50) not null,
crsUnits integer,
CONSTRAINT CoursePK PRIMARY KEY (CourseNo) );


/*-------------------- Faculty --------------------------------*/

CREATE TABLE Faculty(
facNo   char(11) not null,
facFirstName varchar(30) not null,
facLastName  varchar(30) not null,
facCity   varchar(30) not null,
facState  char(2) not null,
facZipCode  char(10) not null,
facRank   char(4),
facHireDate  date,
facSalary  decimal(10,2),
facSupervisor char(11),
facDept   char(6),
CONSTRAINT FacultyPK PRIMARY KEY (FacNo) );


/*-------------------- Offering --------------------------------*/

CREATE TABLE Offering(
offerNo INTEGER not null,
courseNo char(6) not null,
offTerm char(6) not null,
offYear INTEGER not null,
offLocation varchar(30),
offTime varchar(10),
facNo char(11),
offDays char(4),
CONSTRAINT OfferingPK PRIMARY KEY (OfferNo),
CONSTRAINT CourseFK FOREIGN KEY (CourseNo) REFERENCES Course (CourseNo),
CONSTRAINT FacultyFK FOREIGN KEY (FacNo) REFERENCES Faculty (FacNo) );


/*-------------------- Enrollment --------------------------------*/

CREATE TABLE Enrollment (
offerNo  INTEGER not null,
StdNo  char(11) not null,
enrGrade decimal(3,2),
CONSTRAINT EnrollmentPK PRIMARY KEY (OfferNo, StdNo),
CONSTRAINT OfferingFK FOREIGN KEY (OfferNo) REFERENCES Offering (OfferNo)
ON DELETE CASCADE,
CONSTRAINT StudentFK FOREIGN KEY (StdNo) REFERENCES Student (StdNo) ON DELETE CASCADE );

