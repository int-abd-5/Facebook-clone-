#include <iostream>
#include "user_and_pages.h"

using namespace std;

void Control::socialnetworkapp() {
    const char* name = "u2";
    const char* name2 = "p1";
    const char* dates = "17\t4\t2024";
    const char* postptr = "post10";
    setcurrentdate(dates);

    cout << "-------------------------------------------------------------------------------------------------------------\n";
    cout << "Command:                Set current System Date " << dates << "\n";
    cout << "-------------------------------------------------------------------------------------------------------------\n";
    cout << "System Date:            ";
    currentdate.printdate();
    cout << "\n-------------------------------------------------------------------------------------------------------------\n";

    if (SearchUserByID(name)) {
        user* user1 = SearchUserByID(name);
        cout << "Command:                Set current user \"" << name << "\"\n";
        cout << "-------------------------------------------------------------------------------------------------------------\n";
        cout << user1->getname() << " successfully set as Current User\n";
        cout << "-------------------------------------------------------------------------------------------------------------\n";
        cout << "Command:                View Friend List\n";
        cout << "-------------------------------------------------------------------------------------------------------------\n";
        cout << user1->getname() << "  Friend List\n\n";
        user1->printfriend();
        cout << "---------------------------------------------------------------------------------------------------------------\n";
        cout << "Command:                  View Liked Pages\n";
        cout << "---------------------------------------------------------------------------------------------------------------\n";
        cout << user1->getname() << "   Liked Pages\n\n";
        user1->printpages();
        cout << "---------------------------------------------------------------------------------------------------------------\n";
        cout << "Command:                  View TimeLine\n";
        cout << "---------------------------------------------------------------------------------------------------------------\n";
        user1->printtimeline();
        cout << "---------------------------------------------------------------------------------------------------------------\n";

        const char* postId = "post5";
        cout << "Command:                   View Liked List(" << postId << ")\n";
        cout << "---------------------------------------------------------------------------------------------------------------\n";
        posts* post1 = SearchPostsByID(postId);
        if (post1) {
            post1->viewlikedlist();
        }
        cout << "---------------------------------------------------------------------------------------------------------------\n";
        cout << "Command:                   Like Post(" << postId << ")\n";
        likePost(name, postId);
        cout << "Command:                   View Liked List(" << postId << ")\n";
        cout << "---------------------------------------------------------------------------------------------------------------\n";
        if (post1) {
            post1->viewlikedlist();
        }
        cout << "---------------------------------------------------------------------------------------------------------------\n";
        cout << "Command:                   View Page(" << name2 << ")\n";
        cout << "---------------------------------------------------------------------------------------------------------------\n";
        pages* page1 = SearchPageByID(name2);
        if (page1) {
            page1->printtimeline();
        }
        posts* ptr = SearchPostsByID("post4");
        cout << "\n-------------------Command: PrintPost(Post 4)-------------------------\n";
        ptr->printfullinfoall();
        cout << "\n---------------------------------------------------------------------------------------------------------------\n";
        cout << "Command:  CommentonPost(Post4,Good luck for your result)\n";
        cout << "\n-------------------Command: PrintPost(Post 4)-------------------------\n";
        commentOnPost("u7", "post4", "Good luck for your result");
        ptr->printfullinfoall();
        cout << "\n---------------------------------------------------------------------------------------------------------------\n";
        cout << "Command:  CommentonPost(Thank for wishes)\n";
        commentOnPost("u7", "post8", "Thanks for the wishes");
        ptr = SearchPostsByID("post8");
        cout << "\n-------------------Command: PrintPost(Post 4)-------------------------\n";
        ptr->printfullinfoall();
        cout << "---------------------------------------------------------------------------------------------------------------\n";
        cout << "Command:                View Home\n";
        cout << "---------------------------------------------------------------------------------------------------------------\n";
        user1->printhomepage();
        cout << "---------------------------------------------------------------------------------------------------------------\n";
        cout << "Command:                   See memories of user7 \n";
        user1->seememories();
        cout << "---------------------------------------------------------------------------------------------------------------\n";
        cout << "Command:                   Share Memory(post10, Never thought I will be specialist in this field) \n";
        ptr = SearchPostsByID(postptr);
        if (user1->searchtimelline(ptr) == 1) {
            memory* Memory = new memory("Never thought I will be specialist in this field", user1, ptr);
        }
        else {
            cout << "post doesn't belong to user";
        }
        cout << "Command:                   View TimeLine\n";
        user1->printtimeline();
    }
    else {
        cout << " \n\nError User not found:\n\n";
    }
}
int user::numofusers = 0;
int pages::numofpages = 0;
int posts::numofposts = 0;
int comments::numofcomments = 0;
int Activity::numofactivites = 0;
Date Control::currentdate;
int main() {

	Control a;
	a.loadData();
	a.socialnetworkapp();
	return 0;
}
