#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

using namespace std;
class Helper;
class posts;
class Date {
	int day;
	int month;
	int year;

public:
	Date(const char* date = "0");

	void printdate() {
		cout << day << "/" << month << "/" << year;
	}
	int isSameDate(const Date other) const {
		if ((abs(other.day - day) == 2) && (month == other.month) && (year == other.year)) {
			return 2;
		}
		else if ((abs(other.day - day) == 1) && (month == other.month) && (year == other.year)) {
			return 1;
		}
		else if ((abs(other.day - day) == 0) && (month == other.month) && (year == other.year)) {
			return 0;
		}
		else {
			return 5;
		}
	}

	bool ismemory(const Date other) const {
		if ((abs(other.day - day) == 0) && (month == other.month) && (year != other.year)) {
			return 1;
		}
		return 0;
	}
	int ismemoryval(const Date other) const {
		if ((abs(other.day - day) == 0) && (month == other.month) && (year != other.year)) {
			return other.year - year;
		}
		return 0;
	}

	bool operator < (const Date& other) const {
		if (year != other.year)
			return year < other.year;
		if (month != other.month)
			return month < other.month;
		return day < other.day;
	}

	bool operator > (const Date& other) const {
		return other < *this;
	}
};


class object;
class Helper {

public:
	static void StringCopy(char*& dest, char*& src) {
		char* tempDest = dest;
		for (char* tempSrc = src; *tempSrc != '\0'; tempSrc++, tempDest++)
		{
			*tempDest = *tempSrc;
		}
		*tempDest = '\0';
	}

	static char* GetStringFromBuffer(char* buffer)
	{
		int strLen = strlen(buffer);
		char* str = 0;
		if (strLen > 0)
		{
			str = new char[strLen + 1];
			StringCopy(str, buffer);
		}
		return str;
	}
	static int countelements(ifstream& fin) {
		int count = 0;
		auto currentPosition = fin.tellg();
		char buffer[10];
		fin >> buffer;
		while (strcmp(buffer, "-1") != 0) {
			count++;
			fin >> buffer;
		}

		fin.clear();
		fin.seekg(currentPosition);
		return count;
	}

	static char* StringConcatenate(char* string1, char* string2) {
		int len1 = strlen(string1);
		int len2 = strlen(string2);
		int totallen = len1 + len2;
		char* string1new = new char[totallen + 2];
		int i = 0;
		for (; i < len1; i++) {
			string1new[i] = string1[i];
		}
		string1new[i++] = ' ';
		for (int j = 0; j < len2; j++, i++) {
			string1new[i] = string2[j];
		}
		string1new[i] = '\0';
		return string1new;
	}

	static object** generateobject(object** data, int likecount) {
		object** hello = new object * [likecount + 1];
		for (int i = 0; i < likecount; i++) {
			hello[i] = data[i];
		}
		return hello;
	}

	static char* slice(char* namearray) {
		int len = strlen(namearray);
		int len2 = 0;
		char* data = new char[len];
		int hint = 0;
		for (int i = 0; i < len; i++) {
			if ((namearray[i] >= 'A' && namearray[i] <= 'Z') || (namearray[i] >= 'a' && namearray[i] <= 'z') || hint > 0) {
				hint++;
				data[len2] = namearray[i];
				len2++;
			}
		}
		data[len2] = '\0';
		return data;
	}
	static void dateslice(const char* date1, int& day, int& month, int& year) {
		int len = strlen(date1);
		int num = 0;
		int part = 0;

		for (int i = 0; i <= len; i++) {
			if (date1[i] == '\t') {
				if (part == 0) {
					day = num;
					part++;
				}
				else if (part == 1) {
					month = num;
					part++;
				}
				num = 0;
			}
			else {
				if (date1[i] != '\0') {
					num = num * 10 + (date1[i] - '0');
				}
			}
			if (part == 2) {
				year = num;
			}
		}

	}

	static void sortPostsDescending(posts** postArray, int size);

	template <typename t1> static void Destructor(t1** typer, int num) {
		if (typer == nullptr) {
			return;
		}
		for (int i = 0; i < num; i++) {
			if (typer[i] != nullptr) {
				delete typer[i];
				typer[i] = nullptr;
			}
		}
		delete[] typer;
	}
};


class memory;
class posts;
class Control;

class object {
protected:
	char* id;
	posts** timeline;
	int postcount = 0;
	int postadded = 0;

public:
	object() {
		id = nullptr;
		timeline = nullptr;
	}

	virtual char* getid() {
		return id;
	}

	void likepost() {
	}

	virtual char* getname() {
		char* name = nullptr;
		return name;
	}
	virtual void addpost(posts* postptr) = 0;
	virtual void setPostCount(int count = 10) = 0;
	virtual int getpostadded() = 0;
	virtual void printlatest() = 0;
	virtual void printtimeline() = 0;
	virtual void addpost(memory* memptr) = 0;

	virtual ~object() {
		delete[] id;
		Helper::Destructor(timeline, 10);
	}


};


class pages :public object {
private:
	char* pagetitle;
public:
	static int numofpages;

	pages() {
		pagetitle = nullptr;
	}
	void readpageDatafromfile(ifstream& fin) {

		char buffer[200];
		fin >> buffer;
		id = Helper::GetStringFromBuffer(buffer);
		fin.getline(buffer, 100);
		pagetitle = Helper::slice(buffer);
	}
	char* getid() override {
		return id;
	}

	char* getname() override {
		return pagetitle;
	}

	void printfullinfo() {
		cout << getid() << " " << getname() << "\n";
	}

	void addpost(posts* postptr) override {
		if (postadded < postcount) {
			timeline[postadded++] = postptr;
		}
		else {
			cout << "Post limit reached";
		}

	}

	void addpost(memory* memptr) override;
	int getpostadded() override {
		return postadded;
	}

	void setPostCount(int count = 10) override {
		postcount = count;
		timeline = new posts * [postcount];

		for (int i = 0; i < 10; i++)
		{
			timeline[i] = NULL;
		}
	}

	void printlatest() override;
	void printtimeline() override;
	~pages()
	{
		if (pagetitle != nullptr) {
			delete[] pagetitle;
			pagetitle = nullptr;
		}
	}

};


class user : public object {

private:
	char* firstname;
	char* lastname;
	user** friends;
	pages** likedpages;
	int friendcount = 0;
	int pagescount = 0;
	int friendsadded = 0;
	int pagesadded = 0;



public:
	static int numofusers;

	void readUserDatafromfile(ifstream& fin) {

		char buffer[80];
		fin >> buffer;
		id = Helper::GetStringFromBuffer(buffer);
		fin >> buffer;
		firstname = Helper::GetStringFromBuffer(buffer);
		fin >> buffer;
		lastname = Helper::GetStringFromBuffer(buffer);
	}

	void addFriend(user* friendPtr) {
		if (friendsadded < friendcount) {
			friends[friendsadded++] = friendPtr;
		}
		else {
			cout << "friend limit reached";
		}
	}

	void addpage(pages* pagePtr) {
		if (pagesadded < pagescount) {
			likedpages[pagesadded++] = pagePtr;
		}
		else {
			cout << "Page limit reached";
		}
	}

	void setPageCount(int count) {
		pagescount = count;
		likedpages = new pages * [pagescount];
	}

	void setFriendCount(int count) {
		friendcount = count;
		friends = new user * [friendcount];
	}

	void setPostCount(int count = 10)override {
		postcount = count;
		timeline = new posts * [postcount];
		for (int i = 0; i < postcount; i++)
		{
			timeline[i] = NULL;
		}
	}

	void addpost(posts* postptr) override {
		if (postadded < postcount) {
			timeline[postadded++] = postptr;
		}
		else {
			cout << "Post limit reached";
		}

	}

	void addpost(memory* memptr) override;

	user() {
		friends = nullptr, likedpages = nullptr, friendsadded = 0, pagesadded = 0, lastname = nullptr, firstname = nullptr;
	}

	~user() {
		delete[] firstname;
		firstname = nullptr;
		delete[] lastname;
		lastname = nullptr;
		for (int i = 0; i < friendsadded; i++) {
			friends[i] = nullptr;
		}
		friends = nullptr;
		for (int i = 0; i < pagesadded; i++) {
			likedpages[i] = nullptr;
		}
		likedpages = nullptr;

	}

	char* getid() override {
		return id;
	}

	char* getname() override {
		return Helper::StringConcatenate(firstname, lastname);
	}
	int getpostadded() override {
		return postadded;
	}
	void printfullinfo() {
		cout << getid() << "\t" << getname();
	}

	void printfriend() {
		for (int i = 0; i < friendcount; i++) {
			friends[i]->printfullinfo();
			cout << "\n";
		}
	}
	void printpages() {
		for (int i = 0; i < pagescount; i++) {
			likedpages[i]->printfullinfo();
			cout << "\n";
		}
	}
	void printtimeline() override;

	void printlatest() override;

	void printhomepage() {

		printlatest();
		for (int i = 0; i < friendsadded; i++) {
			friends[i]->printlatest();
		}
		for (int i = 0; i < pagesadded; i++) {
			likedpages[i]->printlatest();
		}
	}

	void seememories();

	void printmemory() {

	}


	bool searchtimelline(posts* id) {
		for (int i = 0; i < postadded; i++) {
			if (timeline[i] == id) {
				return 1;
			}
		}
		return 0;
	}
};


class comments;
class Control;
class Activity;



class postcontent {
public:
	postcontent() {

	}

	virtual void printactivity() = 0;
};

class posts {
protected:
	char* id;
	char* text;
	Date date;
	object* sharedby;
	object** likedby;
	comments** comment;
	postcontent* activities;
	int likecount;
	int likeadded = 0;
	int commentadded = 0;
	int totalcomment = 10;
public:
	posts(const char* textInput = nullptr, user* user1 = nullptr);

	static int numofposts;
	void readPostDatafromfile(ifstream& fin, Control& control);
	virtual void printfullinfo();

	void setactivity(int typeof, const char* val);

	void setcommentadded(comments* comment1);
	void viewlikedlist() {
		for (int i = 0; i < likeadded; i++) {
			if (likedby[i] != nullptr) {
				cout << likedby[i]->getid() << "\t" << likedby[i]->getname() << "\n";
			}
			else {
				cout << "\nError Nul placed at likedby\n";
			}
		}
	}

	char* getid() {
		return id;
	}

	Date getdate() {
		return date;
	}
	char* getnewid() {
		const char* prefix = "post";
		char buffer[100];
		sprintf_s(buffer, "%s%d", prefix, numofposts);
		return buffer;
	}

	void addlike(user* ptr) {
		likedby = Helper::generateobject(likedby, likecount);
		likecount++;
		likedby[likeadded++] = ptr;

	}

	void addlike(pages* ptr) {
		likedby = Helper::generateobject(likedby, likecount);
		likecount++;
		likedby[likeadded++] = ptr;
	}


	virtual void printfullinfoall();
	virtual ~posts() {
		if (activities != 0)
		{
			delete activities;
		}
		if (text != 0)
		{
			delete text;
		}
		sharedby = 0;
		if (likedby != 0)
		{
			for (int i = 0; i < likeadded; i++) {
				likedby[i] = 0;
			}
		}
		likedby = 0;
		if (comment != nullptr)
		{
			for (int i = 0; i < commentadded; i++) {
				comment[i] = 0;
			}
			comment = 0;
		}
	}
};

class comments {
	char* id;
	posts* ofpost;
	object* commentby;
	char* text;
public:
	static int numofcomments;

	comments(object* ptr = nullptr, posts* postptr = nullptr, const char* text = nullptr) {
		if (ptr != nullptr && postptr != nullptr && text != nullptr) {
			setid();
			ofpost = postptr;
			commentby = ptr;
			settext(text);
		}
		else {
			text = nullptr;
			ofpost = nullptr;
			commentby = nullptr;
			id = nullptr;
		}
	}

	comments(comments& rhs) {
		strcpy_s(id, strlen(rhs.id), rhs.id);
		ofpost = rhs.ofpost;
		commentby = rhs.commentby;
		strcpy_s(text, strlen(rhs.text), rhs.text);
	}

	char* getid() {
		return id;
	}

	void loadcomment(ifstream& fin, Control& control);

	void printcomment() {
		char* ptr = commentby->getid();
		cout << "\t" << commentby->getname() << ": " << text << "\n";
	}

	void setid() {
		const char* prefix = "c";
		char buffer[100];
		sprintf_s(buffer, "%s%d", prefix, numofcomments);
		id = Helper::GetStringFromBuffer(buffer);
	}

	void setpost(posts* ptr) {
		ofpost = ptr;
	}
	void setcommentby(user* ptr) {
		commentby = ptr;
	}
	void setcommentby(pages* ptr) {
		commentby = ptr;
	}
	void settext(const char* data) {
		int len = strlen(data) + 1;
		text = new char[len];
		strcpy_s(text, len, data);
	}

	~comments()
	{
		commentby = 0;
		if (text != 0)
		{
			delete[] text;
		}
		ofpost = 0;
	}
};


class memory : public posts {
	posts* orignalpost;

public:
	memory(const char* text, user* sharedby, posts* oldpost) : posts(text, sharedby) {
		orignalpost = oldpost;
		sharedby->addpost(this);
	}

	void SeeYourMemories() {

	}

	void printfullinfoall() override;
	~memory()
	{
		if (orignalpost != 0)
		{
			orignalpost = 0;
		}
	}
};

class Activity : public postcontent {

	int type;
	char* value;
public:
	static int numofactivites;
	Activity(int typo = 0, const char* values = " ") {
		type = typo;
		int len = strlen(values) + 1;
		value = new char[len];
		strcpy_s(value, len, values);

	}

	void printactivity() override {
		if (type == 1) {
			cout << " is feeling " << value;
		}
		else if (type == 2) {
			cout << " thinking about " << value;
		}
		else if (type == 3) {
			cout << " Making " << value;
		}
		else if (type == 4) {
			cout << " celebrating " << value;
		}
		else {
			cout << "\n\n\n******** NOT A VALID ACTIVITY TYPE ************\n\n\n";
		}
	}
	~Activity() {
		delete[] value;
	}

};

class Control {
private:
	user** allusers;
	pages** allpage;
	posts** allposts;
	comments** allcomments;

public:
	static Date currentdate;
	Control() {
		allusers = nullptr;
		allpage = nullptr;
		allposts = nullptr;
	}

	void setcurrentdate(const char* date) {
		currentdate = Date(date);
	}

	user* SearchUserByID(const char* id) {
		for (int i = 0; i < user::numofusers; i++) {
			if (allusers[i] == nullptr) {
				cerr << "Error: allposts[" << i << "] is null." << endl;
			}
			else if (allusers[i]->getid() == nullptr) {
				cerr << "Error: Post ID is null for index " << i << "." << endl;
			}
			else if (strcmp(allusers[i]->getid(), id) == 0) {
				return allusers[i];
			}
		}
		return nullptr;
	}
	pages* SearchPageByID(const char* id) {
		for (int i = 0; i < pages::numofpages; i++) {
			if (allpage[i] == nullptr) {
				cerr << "Error: allposts[" << i << "] is null." << endl;
			}
			else if (allpage[i]->getid() == nullptr) {
				cerr << "Error: Post ID is null for index " << i << "." << endl;
			}
			else if (strcmp(allpage[i]->getid(), id) == 0) {
				return allpage[i];
			}
		}
		return nullptr;

	}

	posts* SearchPostsByID(const char* id) {
		for (int i = 0; i < posts::numofposts; i++) {
			if (allposts[i] == nullptr) {
				cerr << "Error: allposts[" << i << "] is null." << endl;
			}
			else if (allposts[i]->getid() == nullptr) {
				cerr << "Error: Post ID is null for index " << i << "." << endl;
			}
			else if (strcmp(allposts[i]->getid(), id) == 0) {
				return allposts[i];
			}
		}
		return nullptr;

	}


	void loadallusers(ifstream& fin) {
		fin >> user::numofusers;
		allusers = new user * [user::numofusers];
		for (int i = 0; i < user::numofusers; i++) {
			allusers[i] = new user();
			allusers[i]->readUserDatafromfile(fin);
		}
	}
	void loadallpages(ifstream& fin) {
		fin >> pages::numofpages;
		allpage = new pages * [pages::numofpages];
		for (int i = 0; i < pages::numofpages; i++) {
			allpage[i] = new pages();
			allpage[i]->readpageDatafromfile(fin);
		}
	}

	void loadfriendandpages(ifstream& fin) {
		char buffer[10];
		while (!fin.eof()) {
			fin >> buffer;
			user* ptr = SearchUserByID(buffer);
			if (ptr != nullptr) {
				int totalfriends = Helper::countelements(fin);
				ptr->setFriendCount(totalfriends);
				fin >> buffer;
				while (strcmp(buffer, "-1") != 0) {
					user* friendPtr = SearchUserByID(buffer);
					if (friendPtr != nullptr) {
						ptr->addFriend(friendPtr);
					}
					fin >> buffer;
				}

				int totalpages = Helper::countelements(fin);
				ptr->setPageCount(totalpages);
				fin >> buffer;
				while (strcmp(buffer, "-1") != 0) {
					pages* pagePtr = SearchPageByID(buffer);
					if (pagePtr != nullptr) {
						ptr->addpage(pagePtr);
					}
					fin >> buffer;
				}
			}
		}
	}

	void loadallposts(ifstream& fin) {
		fin >> posts::numofposts;
		allposts = new posts * [posts::numofposts];
		for (int i = 0; i < posts::numofposts; i++) {
			allposts[i] = new posts();
			allposts[i]->readPostDatafromfile(fin, *this);
		}
	}

	void loadallcomments(ifstream& fin) {
		fin >> comments::numofcomments;
		allcomments = new comments * [comments::numofcomments];
		for (int i = 0; i < comments::numofcomments; i++) {
			allcomments[i] = new comments();
			allcomments[i]->loadcomment(fin, *this);
		}
	}

	void loadallactivities(ifstream& fin) {
		fin >> Activity::numofactivites;
		char buffer[200];
		for (int i = 0; i < Activity::numofactivites; i++) {
			fin >> buffer;
			posts* ptr = SearchPostsByID(buffer);
			if (ptr != nullptr) {
				int type;
				fin >> type;
				fin.getline(buffer, 200);
				ptr->setactivity(type, buffer);
			}
			else {
				cout << "\n\n*POST IS INVALID\n\n";
			}
		}
	}

	void loadData() {
		ifstream fin("users.txt");
		if (!fin) {
			cerr << "Failed to open users.txt" << endl;
			return;
		}
		loadallusers(fin);
		fin.close();
		fin.open("pages.txt");
		loadallpages(fin);
		fin.close();
		fin.open("links.txt");
		loadfriendandpages(fin);
		fin.close();
		fin.open("posts.txt");
		loadallposts(fin);
		fin.close();
		fin.open("comments.txt");
		loadallcomments(fin);
		fin.close();
		fin.open("activity.txt");
		loadallactivities(fin);
		fin.close();
	}

	void socialnetworkapp();

	void likePost(const char* Id, const char* postId) {
		user* userPtr = SearchUserByID(Id);
		pages* pagePtr = SearchPageByID(Id);
		posts* postPtr = SearchPostsByID(postId);
		if (userPtr && postPtr) {
			postPtr->addlike(userPtr);
		}
		else if (pagePtr && postPtr) {
			postPtr->addlike(pagePtr);
		}
	}

	void commentOnPost(const char* Id, const char* postId, const char* text) {
		user* userPtr = SearchUserByID(Id);
		pages* pagePtr = SearchPageByID(Id);
		posts* postPtr = SearchPostsByID(postId);
		if (userPtr && postPtr) {
			allcomments = updatecomment(allcomments);
			allcomments[comments::numofcomments] = new comments(userPtr, postPtr, text);
			postPtr->setcommentadded(allcomments[comments::numofcomments]);
			comments::numofcomments = comments::numofcomments + 1;
		}
		else if (pagePtr && postPtr) {
			allcomments = updatecomment(allcomments);
			allcomments[comments::numofcomments] = new comments(pagePtr, postPtr, text);
			postPtr->setcommentadded(allcomments[comments::numofcomments]);
			comments::numofcomments = comments::numofcomments + 1;
		}
	}

	comments** updatecomment(comments** totalcomments) {
		comments** newcomments = new comments * [comments::numofcomments + 1];
		for (int i = 0; i < comments::numofcomments; i++) {
			newcomments[i] = totalcomments[i];
		}

		return newcomments;
	}

	~Control() {
		Helper::Destructor(allusers, user::numofusers);
		Helper::Destructor(allpage, pages::numofpages);
		Helper::Destructor(allcomments, comments::numofcomments);

	}

};

void posts::readPostDatafromfile(ifstream& fin, Control& control) {
	char buffer[1000];
	fin >> buffer;
	id = Helper::GetStringFromBuffer(buffer);
	fin.getline(buffer, 1000);
	fin.getline(buffer, 1000);
	const char* name = Helper::GetStringFromBuffer(buffer);
	date = Date(name);

	fin.getline(buffer, 1000);
	text = Helper::GetStringFromBuffer(buffer);

	fin >> buffer;
	user* userPtr = control.SearchUserByID(buffer);
	if (userPtr != nullptr) {
		sharedby = userPtr;
		if (userPtr->getpostadded() == 0) {
			userPtr->setPostCount();
		}
		userPtr->addpost(this);

	}
	else {
		pages* pagePtr = control.SearchPageByID(buffer);
		if (pagePtr != nullptr) {
			sharedby = pagePtr;
			if (pagePtr->getpostadded() == 0) {
				pagePtr->setPostCount();
			}
			pagePtr->addpost(this);
		}
		else {
			cout << "\n\n ****** USER NOT FOUND WHO SHARED POST ******* \n\n";
		}
	}
	likecount = Helper::countelements(fin);
	likedby = new object * [likecount];
	for (int i = 0; i < likecount; i++) {
		fin >> buffer;

		user* userPtr = control.SearchUserByID(buffer);
		if (userPtr != nullptr) {
			likedby[likeadded] = userPtr;
			likeadded++;
		}
		else {
			pages* pagePtr = control.SearchPageByID(buffer);
			if (pagePtr != nullptr) {
				likedby[likeadded] = pagePtr;
				likeadded++;
			}
			else {
				cout << "\n\n ****** USER NOT FOUND WHO LIKED POST ******* \n\n";
			}
		}
	}
	fin >> buffer;
}

void user::printtimeline() {
	Helper::sortPostsDescending(timeline, postadded);
	for (int i = 0; i < postadded; i++) {
		timeline[i]->printfullinfoall();
		cout << "\n\n\n";
	}
}

void pages::printtimeline() {
	Helper::sortPostsDescending(timeline, postadded);
	for (int i = 0; i < postadded; i++) {
		timeline[i]->printfullinfoall();
		cout << "\n\n\n";
	}
}

void comments::loadcomment(ifstream& fin, Control& control) {
	char buffer[1000];
	fin >> buffer;
	id = Helper::GetStringFromBuffer(buffer);
	fin >> buffer;
	posts* ptr = control.SearchPostsByID(buffer);
	if (ptr != nullptr) {
		ptr->setcommentadded(this);
		ofpost = ptr;
		fin >> buffer;
		object* optr = control.SearchPageByID(buffer);
		object* optr2 = control.SearchUserByID(buffer);
		if (optr != nullptr) {
			commentby = optr;
		}
		else if (optr2 != nullptr) {
			commentby = optr2;
		}
		else {
			cerr << "Error commented by not found";
			commentby = nullptr;
		}
		fin.getline(buffer, 1000);
		text = Helper::GetStringFromBuffer(buffer);
	}

}

void posts::printfullinfo() {

	cout << "\t" << text;
	if (date.isSameDate(Control::currentdate) == 0) {
		cout << " ~~~~ 2 hour ago";
	}
	else if ((date.isSameDate(Control::currentdate) == 1)) {
		cout << " ~~~~~ 1 day ago";
	}
	else if ((date.isSameDate(Control::currentdate) == 2)) {
		cout << " ~~~~~~ 2 day ago";
	}
	else {
		cout << "   (";
		date.printdate();
		cout << ")\n";
	}
	if (comment != nullptr) {
		for (int i = 0; i < commentadded; i++) {
			comment[i]->printcomment();
		}
	}

}

void posts::printfullinfoall() {
	if (activities == nullptr) {
		cout << sharedby->getname() << "\t";
		if (date.isSameDate(Control::currentdate) == 0) {
			cout << "\t(2 hour ago)";
		}
		else if ((date.isSameDate(Control::currentdate) == 1)) {
			cout << "\t(1 day ago)";
		}
		else if ((date.isSameDate(Control::currentdate) == 2)) {
			cout << "\t(2 day ago)";
		}
		else {
			cout << "\t(";
			date.printdate();
			cout << ")";
		}
		cout << ":\n" << text << "\n";
		if (comment != nullptr) {
			for (int i = 0; i < commentadded; i++) {
				comment[i]->printcomment();
			}
		}
	}
	else if (activities != nullptr) {
		cout << sharedby->getname();
		cout << " is ";
		activities->printactivity();
		if (date.isSameDate(Control::currentdate) == 0) {
			cout << "\t(2 hour ago)";
		}
		else if ((date.isSameDate(Control::currentdate) == 1)) {
			cout << "\t(1 day ago)";
		}
		else if ((date.isSameDate(Control::currentdate) == 2)) {
			cout << "\t(2 day ago)";
		}
		else {
			cout << "\t(";
			date.printdate();
			cout << ")";
		}
		cout << ":\n" << text << "\n";
		if (comment != nullptr) {
			for (int i = 0; i < commentadded; i++) {
				comment[i]->printcomment();
			}
		}
	}
}

Date::Date(const char* date) {
	Helper::dateslice(date, day, month, year);
}

void pages::printlatest() {
	int i = 0;
	Date newdate;
	while (i < postadded) {
		cout << "\n";
		newdate = timeline[i]->getdate();
		if (newdate.isSameDate(Control::currentdate) <= 2) {
			timeline[i]->printfullinfoall();
		}
		i++;
	}
}

void user::printlatest() {
	int i = 0;
	Date newdate;
	while (i < postadded) {
		cout << "\n";
		newdate = timeline[i]->getdate();
		if (newdate.isSameDate(Control::currentdate) <= 2) {
			timeline[i]->printfullinfoall();
		}
		i++;
	}
}

void posts::setactivity(int typeof, const char* val) {
	activities = new Activity(typeof, val);
}

void user::addpost(memory* memptr) {
	if (postadded < postcount) {
		timeline[postadded++] = memptr;
	}
	else {
		cout << "Post limit reached";
	}
}

void pages::addpost(memory* memptr) {
	if (postadded < postcount) {
		timeline[postadded++] = memptr;
	}
	else {
		cout << "Post limit reached";
	}

}


posts::posts(const char* textInput, user* user1) {
	id = getnewid();
	if (textInput != nullptr) {
		text = new char[strlen(textInput) + 1];
		strcpy_s(text, strlen(textInput) + 1, textInput);
	}
	else {
		text = nullptr;
	}
	date = Control::currentdate;
	sharedby = user1;

	likedby = nullptr;
	comment = new comments * ();
	activities = nullptr;
}

void memory::printfullinfoall() {
	cout << "~~~ " << sharedby->getname() << " shared a memory ~~~ (";
	if (date.isSameDate(Control::currentdate) == 0) {
		cout << "2 hour ago";
	}
	else if ((date.isSameDate(Control::currentdate) == 1)) {
		cout << "1 day ago";
	}
	else if ((date.isSameDate(Control::currentdate) == 2)) {
		cout << "2 day ago";
	}
	else {
		date.printdate();
	}
	cout << ")";
	cout << " from " << memory::orignalpost->getdate().ismemoryval(Control::currentdate) << " years ago ~~~\n";
	cout << text << '\n';
	orignalpost->printfullinfoall();
}

void posts::setcommentadded(comments* comment1) {

	comment[commentadded] = comment1;
	commentadded++;

}

void Helper::sortPostsDescending(posts** postArray, int size) {
	bool swapped;
	do {
		swapped = false;
		for (int i = 0; i < size - 1; i++) {
			if (postArray[i]->getdate() < postArray[i + 1]->getdate()) {
				posts* temp = postArray[i];
				postArray[i] = postArray[i + 1];
				postArray[i + 1] = temp;
				swapped = true;
			}
		}
	} while (swapped);
}

void user::seememories() {
	for (int i = 0; i < postadded; i++) {
		if ((timeline[i]->getdate()).ismemory(Control::currentdate) == 1) {
			cout << "~~~~ Memory from " << timeline[i]->getdate().ismemoryval(Control::currentdate)<<" years ago \n";
			timeline[i]->printfullinfoall();
		}
	}
}