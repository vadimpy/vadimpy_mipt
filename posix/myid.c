#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>
#include <sys/types.h>
#include <grp.h>

#define N 100

int main()
{
	
	int uid;
	int gid;
	int groups_value;
	gid_t groups[N];
	struct passwd* user_info;
	struct group* group_info;
	int i;

	uid = getuid();
	gid = getgid();
	groups_value = getgroups(N, groups);
	user_info = getpwuid(uid);

	printf("uid=%d(%s) gid=%d(%s) groups=", uid, user_info->pw_name, gid, user_info->pw_name);
	
	for(i = 0; i < groups_value - 1; ++i)
	{
		group_info = getgrgid(groups[i]);
		printf("%d(%s),", groups[i], group_info->gr_name);
	}
	printf("%d(%s)", groups[i], getgrgid(groups[i])->gr_name);

	return 0;
}
