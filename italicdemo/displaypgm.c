#include <actsemi.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include <dirent.h>

#include "image.c"

#define VERSION "R1.02"

int p1CoreLoop(void);
void p1EnqueueKey(void *input);
int p1_control(int cmd, void *data);

/* Table of functions called by the framework to control the "emulator". */
void *p1apitbl[] = {
  p1CoreLoop,
  p1EnqueueKey,
  p1_control
};
const void *p1apitbl_p = p1apitbl;

char t[256];	/* text buffer */
int fd;
FILE* fp;


void  __attribute__ ((section (".init"))) _init_proc(void)
{
  /* Now we're finally being good citizens and submitting our interface. */
  api_install(7, p1apitbl);
}

void __attribute__ ((section (".fini"))) _term_proc(void)
{
}

/* No idea what this is good for. */
uint32_t general_plugin_info = 0;
uint32_t *get_plugin_info(void)
{
  return &general_plugin_info;
}

/* Version symbol the updater uses to determine if it should update an
   emulator. This demo will usually be run by our own launcher, which
   doesn't care about the version. */
const char *P1_SO_VERSION = VERSION;

struct rect {
  uint32_t w;
  uint32_t h;
};

struct rect screen_size;
uint16_t *screen_fb;
int redraw = 0;

/* Worker function called periodically by the framework. */
int p1CoreLoop(void)
{
  static unsigned int last_run = 0;
  /* The framework will incessantly call the API functions in a loop, so
     we need to give up some CPU time for our demo thread. */
  usleep(10000);
  struct timeval tv;
  gettimeofday(&tv, NULL);
  unsigned int elapsed = tv.tv_sec * 1000 + tv.tv_usec / 1000 - last_run;
  if (elapsed < 16) {
    return 0;
  }
  last_run = tv.tv_sec * 1000 + tv.tv_usec / 1000;


  // draw some graphics
	
	
	int i;
	for (i=0; i < 640 * 480; i++) {
		if (bits[i] > 0) {
			screen_fb[i] = 0xffff;
		}
	}
	
  redraw = 1;
  return 0;
}

void p1EnqueueKey(void *input)
{
  (void)input;
}

struct cmd_22 {
  uint32_t key_code_mode;
  uint32_t key_code[0x10];
  uint32_t key_file_len;
};

int cmd_22(struct cmd_22 *data)
{
  (void)data;
  return 0;
}

int max_screen_dimensions(struct rect *r)
{
	sprintf(t, "screen size %d/%d\n", (int)r->w, (int)r->h);
	write(fd, t, strlen(t));
  screen_size = *r;
  return 0;
}

struct rect_form {
  uint32_t w;
  uint32_t h;
  uint32_t format;
};

/* Tell the system what kind of frame buffer we would like to have. */
int get_our_dimensions(struct rect_form *rf)
{
  rf->w = 640;
  rf->h = 480;
  rf->format = 1;
  return 0;
}

/* Called by the framework to change the state of the "emulator". */
int p1_control(int cmd, void *data)
{
  /* All commands should (except command 17 (redraw)) should always return 0.
     If they don't, the framework will assume there has been an error and
     abort. */
  int ret;
  
  switch (cmd) {
    case 0:	/* init */
      return 0;
    case 1:	/* reset */
      return 0;
    case 2:	/* game name */
      return 0;
    case 3:	/* shutdown */
      return 0;
    case 4:
      return 0;
    case 7:	/* sound enable */
      return 0;
    case 10:	/* suspend */
      return 0;
    case 13:	/* get our dimensions, format */
      return get_our_dimensions((struct rect_form *)data);
    case 14:	/* set frame buffer */
      screen_fb = *((uint16_t **)data);
      return 0;
    case 15:
      return max_screen_dimensions((struct rect*)data);
    case 16:	/* screen mode */
      return 0;
    case 17:	/* get redraw flag */
      /* If we return 1 here, the framework will blit the frame buffer
         to the device screen. */
      ret = redraw;
      redraw = 0;
      return ret;
    case 18:	/* input mode */
      return 0;
    case 22:
      return cmd_22((struct cmd_22 *)data);
    default:
      return 0;
  }
}

asm(
".section .dlsym,\"a\"\n"
".word P1_SO_VERSION\n"
".word _dlstr_P1_SO_VERSION\n"
".word get_plugin_info\n"
".word _dlstr_get_plugin_info\n"
".word p1apitbl\n"
".word _dlstr_api_table\n"
".section .dlstr,\"a\"\n"
"_dlstr_P1_SO_VERSION:\n"
".string \"P1_SO_VERSION\\0\"\n"
"_dlstr_get_plugin_info:\n"
".string \"get_plugin_info\\0\"\n"
"_dlstr_api_table:\n"
".string \"api_table\\0\"\n"
);
