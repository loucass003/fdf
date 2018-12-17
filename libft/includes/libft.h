/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelievr <llelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 14:23:49 by llelievr          #+#    #+#             */
/*   Updated: 2018/12/13 22:54:06 by llelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIBFT_H
# define FT_LIBFT_H
# include <string.h>
# include <sys/types.h>
# define BUFF_SIZE 4096

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_buff
{
	char			*buf;
	ssize_t			len;
}					t_buff;

typedef struct		s_vec3
{
	float			x;
	float			y;
	float			z;
}					t_vec3;

typedef struct		s_vec2
{
	float			x;
	float			y;
}					t_vec2;

typedef struct		s_pixel
{
	int				x;
	int				y;
}					t_pixel;

typedef struct		s_mat4_data
{
	float			m00;
	float			m01;
	float			m02;
	float			m03;
	float			m10;
	float			m11;
	float			m12;
	float			m13;
	float			m20;
	float			m21;
	float			m22;
	float			m23;
	float			m30;
	float			m31;
	float			m32;
	float			m33;
}					t_mat4_data;

typedef	union		u_mat4
{
	float			a[4][4];
	t_mat4_data		d;
}					t_mat4;

int					ft_gnl(const int fd, char **line);

void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_realloc(void *o_ptr, size_t oldsize, size_t newsize);

void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);

size_t				ft_strlen(const char *s);
char				*ft_strdup(const char *s1);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strnstr(const char *s, const char *need, size_t n);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);

char				*ft_strnew(size_t size);
void				ft_strdel(char **str);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(const char *s, char c);

int					ft_atoi(const char *str);

char				*ft_itoa(int n);

int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);

void				ft_putchar(char c);
void				ft_putstr(const char *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(const char *s, int fd);
void				ft_putendl_fd(char const *s1, int fd);
void				ft_putnbr_fd(int n, int fd);

t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *n);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

int					ft_abs(int n);
float				ft_absf(float n);
int					ft_isspace(char c);
float				ft_sqrt(int f);
int					ft_pow(int n, int pow);
void				ft_foreach(void **tab, size_t len, void (*f)(void **));
void				ft_lstput(t_list **alst, t_list *n);

/*
** Graphics Utils
*/

t_pixel				ft_pixel_add(t_pixel a, t_pixel b);
t_pixel				ft_pixel_sub(t_pixel a, t_pixel b);
t_pixel				ft_pixel_div(t_pixel a, t_pixel b);
t_pixel				ft_pixel_mul(t_pixel a, t_pixel b);

t_vec3				ft_vec3_add(t_vec3 a, t_vec3 b);
t_vec3				ft_vec3_sub(t_vec3 a, t_vec3 b);
t_vec3				ft_vec3_div(t_vec3 a, t_vec3 b);
t_vec3				ft_vec3_mul(t_vec3 a, t_vec3 b);
float				ft_vec3_dot(t_vec3 a, t_vec3 b);
float				ft_vec3_len(t_vec3 v);
t_vec3				ft_vec3_norm(t_vec3 v);
t_vec3				ft_vec3_cross(t_vec3 a, t_vec3 b);
t_vec3				ft_vec3_inv(t_vec3 v);

t_vec2				ft_vec2_add(t_vec2 a, t_vec2 b);
t_vec2				ft_vec2_sub(t_vec2 a, t_vec2 b);
t_vec2				ft_vec2_div(t_vec2 a, t_vec2 b);
t_vec2				ft_vec2_mul(t_vec2 a, t_vec2 b);
float				ft_vec2_dot(t_vec2 a, t_vec2 b);
float				ft_vec2_len(t_vec2 v);
t_vec2				ft_vec2_norm(t_vec2 v);
t_vec2				ft_vec2_inv(t_vec2 v);

t_mat4				ft_mat4_identity(void);
t_mat4				ft_mat4_translation(t_vec3 t);
t_mat4				ft_mat4_rotation(t_vec3 angles);
t_mat4				ft_mat4_scale(t_vec3 s);
t_mat4				ft_mat4_mul(t_mat4 a, t_mat4 b);
t_vec3				ft_mat4_mulv(t_mat4 m, t_vec3 v);

#endif
