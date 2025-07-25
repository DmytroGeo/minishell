/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 10:18:04 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/25 15:10:39 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// }

		///////////////////////
		// dgeorgiy@c1r4s5:~/42_cursus_personal/minishell$ <<
		// bash: syntax error near unexpected token `newline'
		// dgeorgiy@c1r4s5:~/42_cursus_personal/minishell$ cat <<hello
		// > hii
		// > $USER
		// > hello
		// hii
		// dgeorgiy
		// dgeorgiy@c1r4s5:~/42_cursus_personal/minishell$ cat << 'hello'
		// > hiiui
		// > $USER
		// > 'hello'
		// > hello
		// hiiui
		// $USER
		// 'hello'
		// dgeorgiy@c1r4s5:~/42_cursus_personal/minishell$ cat << "hello"
		// > hii
		// > $USER
		// > hello
		// hii
		// $USER
		// dgeorgiy@c1r4s5:~/42_cursus_personal/minishell$ cat << hel"l"o
		// > hi
		// > $USER
		// > hel"l"o
		// > hello
		// hi
		// $USER
		// hel"l"o
		// dgeorgiy@c1r4s5:~/42_cursus_personal/minishell$
		///////////////////////////