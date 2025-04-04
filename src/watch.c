/* Based on swomf/mfw */

#include <libgen.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/inotify.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#define EVENT_SIZE (sizeof(struct inotify_event))

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Usage: ./watch <filename>\n");
    exit(EXIT_FAILURE);
  }
  const char *file_path = argv[1];
  const char *file_name = basename(argv[1]);
  const char *dir_name = dirname(argv[1]);
  const char *cmd = argv[2];

  /* filename is: (1) an existing file (2) readable (3) not a directory */
  FILE *file = fopen(file_path, "r");
  if (file == NULL) {
    fprintf(stderr, "Couldn't stat %s as file\n", file_path);
    goto end;
  }
  fclose(file);

  int length, i = 0;
  int wd, fd;
  char buf[EVENT_SIZE + NAME_MAX];

  fd = inotify_init();
  if (fd < 0) {
    perror("Couldn't initialize inotify");
    exit(EXIT_FAILURE);
  }

  /* Watch its dir instead. https://unix.stackexchange.com/a/312359 */
  wd = inotify_add_watch(fd, dir_name, IN_MODIFY | IN_DELETE);

  system("clear");
  system(cmd);

  while (1) {
    i = 0;
    length = read(fd, buf, EVENT_SIZE + NAME_MAX);
    if (length < 0) {
      perror("Couldn't read file descriptor");
      exit(EXIT_FAILURE);
    }

    while (i < length) {
      struct inotify_event *event = (struct inotify_event *)&buf[i];
      if (!event->len)
        continue;
      i += EVENT_SIZE + event->len;

      int is_file_arg = strcmp(event->name, file_name) == 0 ? 1 : 0;
      if (event->mask & IN_MODIFY && !(event->mask & IN_ISDIR) && is_file_arg) {
        system("clear");
        system(cmd);
      }

      if (event->mask & IN_DELETE && !(event->mask & IN_ISDIR) && is_file_arg) {
        fprintf(stderr, "File deleted. Closing.");
        goto end;
      }
    }
  }
end:

  inotify_rm_watch(fd, wd);
  close(fd);
  system("tput reset");

  return EXIT_FAILURE;
}
