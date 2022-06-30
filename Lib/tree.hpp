/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mxu <mxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 19:01:33 by mxu               #+#    #+#             */
/*   Updated: 2022/01/10 14:39:29 by mxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RED_BLACK_TREE_HPP_
#define RED_BLACK_TREE_HPP_

#include <memory>
#include <algorithm>
#include <limits>
#include <utility>

#include "utillity.hpp"
#include "iterator.hpp"
#include "type_traits.hpp"

// Adapted from Red-Black tree on GeeksforGeeks at:
// 	https://www.geeksforgeeks.org/red-black-tree-set-3-delete-2/
// and from libc++ implementation of __tree located on Mac:
// 	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/include/c++/v1

namespace ft
{

template <class Tp, class Compare, class Allocator>	class RBTree;
template <class Tp, class NodePtr, class DiffType> 	class tree_iterator;
template <class Tp, class NodePtr, class DiffType> 	class tree_const_iterator;
template <class Tp>									class Node;

enum COLOR {RED, BLACK};

template <class Tp>
class Node 
{
public:
	Tp 		val;
	COLOR 	color;
	Node 	*left, *right, *parent;

	Node(Tp val) : val(val) { parent = left = right = nullptr; color = RED; }

	Node *uncle() 
	{
		if (parent == nullptr or parent->parent == nullptr)
			return nullptr;
		if (parent->isOnLeft())
			return parent->parent->right;
		else
			return parent->parent->left;
	}

	bool isOnLeft() { return this == parent->left; }

	Node *sibling() 
	{
		if (parent == nullptr)
			return nullptr;
		if (isOnLeft())
			return parent->right;
		return parent->left;
	}

	// moves node down and moves given node in its place
	void moveDown(Node *nParent) 
	{
		if (parent != nullptr) 
		{
			if (isOnLeft()) 
				parent->left = nParent;
			else 
				parent->right = nParent;
		}
		nParent->parent = parent;
		parent = nParent;
	}

	bool hasRedChild() 
	{
		return (left != nullptr and left->color == RED) ||
			   (right != nullptr and right->color == RED);
	}

	template <class, class, class> friend class 	RBTree;
};

//888888888888888888888888888888888MINGXINXU888888888888888888888888888888888

template <class node_pointer>
node_pointer tree_min(node_pointer x) 
{
	node_pointer temp = x;
	while (temp->left != nullptr)
		temp = temp->left;
	return temp;
}

template <class node_pointer>
node_pointer tree_max(node_pointer x)
{
	node_pointer temp = x;
	while (temp->right != nullptr)
		temp = temp->right;
	return temp;
}

template <class node_pointer>
node_pointer tree_next(node_pointer x)
{
	if (x->parent == nullptr)
		return x;
	if (x->right != nullptr)
		return tree_min(x->right);
	while (!x->isOnLeft())
		x = x->parent;
	return x->parent;
}

template <class node_pointer>
node_pointer tree_prev(node_pointer x)
{
	if (x->left != nullptr)
		return tree_max(x->left);
	while (x->isOnLeft())
		x = x->parent;
	return x->parent;
}

//888888888888888888888888888888888MINGXINXU888888888888888888888888888888888

template <class Tp, class NodePtr, class DiffType>
class tree_iterator
{
    NodePtr        _ptr;

public:
    typedef ft::bidirectional_iterator_tag	iterator_category;
    typedef Tp                         		value_type;
    typedef DiffType                    	difference_type;
    typedef value_type&                 	reference;
    typedef value_type*                    	pointer;

    tree_iterator() {}

    reference       operator*() const   	{ return _ptr->val; }
    pointer         operator->() const  	{ return &_ptr->val; }

    tree_iterator&  operator++()			{ _ptr = tree_next(_ptr); return *this; }
    tree_iterator   operator++(int)     	{ tree_iterator t(*this); ++(*this); return t; }
    tree_iterator&  operator--()			{ _ptr = tree_prev(_ptr); return *this; }
    tree_iterator   operator--(int)     	{ tree_iterator t(*this); --(*this); return t; }

	friend
		bool operator==(const tree_iterator& x, const tree_iterator& y)
		{ return x._ptr == y._ptr; }
	friend
		bool operator!=(const tree_iterator& x, const tree_iterator& y)
		{ return !(x == y); }

private:
    explicit        tree_iterator(NodePtr p) : _ptr(p) {}
	//explicit		tree_iterator(const tree_iterator& t) : _ptr(t._ptr) {}
    NodePtr    		_get_np() const { return _ptr; }

    template <class, class, class> friend class			RBTree;
    template <class, class, class> friend class			tree_const_iterator;
    template <class> friend class 						map_iterator;
    template <class, class, class, class> friend class 	map;
    template <class, class, class> friend class 		set;
};

//888888888888888888888888888888888MINGXINXU888888888888888888888888888888888

template <class Tp, class NodePtr, class DiffType>
class tree_const_iterator
{
    NodePtr        _ptr;

public:
    typedef ft::bidirectional_iterator_tag		iterator_category;
    typedef Tp                         			value_type;
    typedef DiffType                    		difference_type;
    typedef const value_type&              		reference;
    typedef const value_type*             		pointer;

private:
	typedef tree_iterator<value_type, NodePtr, difference_type> non_const_iterator;

public:
    tree_const_iterator() {}
	tree_const_iterator(non_const_iterator p) : _ptr(p._ptr) {}


    reference       		operator*() const   { return _ptr->val; }
    pointer         		operator->() const  { return &_ptr->val; }

    tree_const_iterator&  	operator++()		{ _ptr = tree_next(_ptr); return *this; }
    tree_const_iterator   	operator++(int)     { tree_const_iterator t(*this); ++(*this); return t; }
    tree_const_iterator&  	operator--()		{ _ptr = tree_prev(_ptr); return *this; }
    tree_const_iterator   	operator--(int)     { tree_const_iterator t(*this); --(*this); return t; }

	friend
		bool operator==(const tree_const_iterator& x, const tree_const_iterator& y)
		{ return x._ptr == y._ptr; }
	friend
		bool operator!=(const tree_const_iterator& x, const tree_const_iterator& y)
		{ return !(x == y); }

private:
    explicit        tree_const_iterator(NodePtr p) : _ptr(p) {}
    NodePtr    		_get_np() const { return _ptr; }

    template <class, class, class> friend class			RBTree;
    template <class> friend class 						map_const_iterator;
    template <class, class, class, class> friend class 	map;
    template <class, class, class> friend class 		set;
};

//888888888888888888888888888888888MINGXINXU888888888888888888888888888888888

template <class Tp, class Compare, class Allocator>
class RBTree
{
public:
	typedef Tp																value_type;
	typedef Compare															hybrid_compare;
	typedef Allocator														allocator_type;
	typedef std::allocator_traits<allocator_type>							allocator_traits;
	typedef std::allocator<Node<Tp> >										node_allocator_type;
	typedef std::allocator_traits<node_allocator_type>						node_allocator_traits;
private:
	typedef typename hybrid_compare::first_argument_type					key_type;
	typedef typename hybrid_compare::third_argument_type					key_compare;
public:
    typedef typename allocator_type::pointer            					pointer;  // pointer to ft::pair<const Key, T> in case of map
    typedef typename allocator_type::const_pointer      					const_pointer;
    typedef typename allocator_type::size_type          					size_type;
    typedef typename allocator_type::difference_type    					difference_type;

	typedef typename node_allocator_type::value_type						node_type;
	typedef typename node_allocator_type::pointer							node_pointer;
	typedef typename node_allocator_type::const_pointer						const_node_pointer;

	typedef tree_iterator<value_type, node_pointer, difference_type>		iterator;
	typedef tree_const_iterator<value_type, node_pointer, difference_type>	const_iterator;

private:
	node_pointer				end_node;	// Node<Tp> *end_node; end_node->left = root;
	size_type					tree_size;
	hybrid_compare				vc;
	node_allocator_type			n_alloc;
	

private:
	node_pointer				construct_node(const value_type& v)
	{
		node_pointer ret = node_allocator_traits::allocate(n_alloc, 1);
		node_allocator_traits::construct(n_alloc, &(ret->val), v);
		ret->color = RED;
		ret->left = ret->right = ret->parent = nullptr;
		return ret;
	}

	void						destruct_node(node_pointer nd)
	{
		if (nd != nullptr)
		{
			nd->left = nd->right = nd->parent = nullptr;
			node_allocator_traits::destroy(n_alloc, &(nd->val));
			node_allocator_traits::deallocate(n_alloc, nd, 1);
		}
	}

	void						destroy(node_pointer nd)
	{
		if (nd != nullptr)
		{
			destroy(nd->left);
			destroy(nd->right);
			destruct_node(nd);
		}
	}

public:
	RBTree(const hybrid_compare& v_comp = hybrid_compare(), 
		   const node_allocator_type& node_alloc = node_allocator_type()) 
		: tree_size(0), vc(v_comp), n_alloc(node_alloc)
	{
		end_node = node_allocator_traits::allocate(n_alloc, 1);
		end_node->left = end_node->right = end_node->parent = nullptr;
	}

	RBTree(const RBTree& t)
		: tree_size(t.get_size()), vc(t.get_vc()), n_alloc(t.get_n_alloc())
	{
		end_node = node_allocator_traits::allocate(n_alloc, 1);
		end_node->left = end_node->right = end_node->parent = nullptr;
		if (t.size() > 0)
			insert(t.begin(), t.end());
	}

	RBTree&	operator=(const RBTree& t)
	{
		if (this != &t)
		{
			clear();
			vc = t.get_vc();
			if (n_alloc != t.get_n_alloc())
			{
				destruct_node(end_node);
				n_alloc = t.get_n_alloc();
				end_node = node_allocator_traits::allocate(n_alloc, 1);
				end_node->left = end_node->right = end_node->parent = nullptr;
			}
			if (t.size() > 0)
				insert(t.begin(), t.end());
		}
		return *this;
	}
	
	~RBTree() 								
	{ 
		destroy(get_root()); 
		destruct_node(end_node); 
	}

	node_pointer				get_end_node() 			{ return end_node; }	
	node_pointer				get_root() const 		{ return end_node->left; }
	hybrid_compare&				get_vc()				{ return vc; }
	const hybrid_compare&		get_vc() const			{ return vc; }
	node_allocator_type&		get_n_alloc()			{ return n_alloc; }
	const node_allocator_type&	get_n_alloc() const		{ return n_alloc; }
	const size_type&			get_size() const 		{ return tree_size; }

	void				clear()
	{
		destroy(get_root());
		tree_size = 0;
		end_node->left = nullptr;
	}

	void				swap(RBTree& t)
	{
		std::swap(end_node, t.end_node);
		std::swap(tree_size, t.tree_size);
		std::swap(n_alloc, t.n_alloc);
		std::swap(vc, t.vc);
		if (tree_size > 0)
			end_node->left->parent = end_node;
		if (t.size() > 0)
			t.end_node->left->parent = t.end_node;
	}

	iterator			begin() 			
	{ 
		if (tree_size == 0)
			return iterator(end_node);
		else
			return iterator(tree_min(get_root()));
	}

	const_iterator		begin() const
	{ 
		if (tree_size == 0)
			return const_iterator(end_node);
		else
			return const_iterator(tree_min(get_root()));
	}

	iterator			end() 				{ return iterator(end_node); }

	const_iterator		end() const 		{ return const_iterator(end_node); }

	const size_type&	size() const 		{ return tree_size; }
	
	size_type			max_size() const	
	{ 
		return std::min<size_type>(node_allocator_traits::max_size(n_alloc),
								   std::numeric_limits<difference_type>::max()); 
	}
	
	ft::pair<iterator, bool>	insert(const value_type& v)	
	{ 
		ft::pair<node_pointer, bool>  nd = insertByVal(v); 
		if (nd.second == true)
			tree_size++;
		return ft::make_pair(iterator(nd.first), nd.second);
	}

	iterator					insert(const_iterator i, const value_type& v)
	{
		ft::pair<node_pointer, bool>  nd = insertByValInd(i, v); 
		if (nd.second == true)
			tree_size++;
		return iterator(nd.first);
	}

	void						insert(iterator first, iterator last)
	{
		for(; first != last; ++first)
			insert(*first);
	}

	void						insert(const_iterator first, const_iterator last)
	{
		for(; first != last; ++first)
			insert(*first);
	}

	template <class InputIterator>
    void                        insert(InputIterator first, 
			typename ft::enable_if<std::__is_input_iterator<InputIterator>::value &&
            !std::__is_forward_iterator<InputIterator>::value, InputIterator>::type last)
	{
		for(; first != last; ++first)
			insert(*first);
	}

    template <class ForwardIterator>
    void                        insert(ForwardIterator first, 
			typename ft::enable_if<std::__is_forward_iterator<ForwardIterator>::value, ForwardIterator>::type last)
    {
		for(; first != last; ++first)
			insert(*first);
	}
	
	size_type					erase(const key_type& k)
	{
		if (!deleteByKey(k))
			return 0;
		tree_size--;
		if (tree_size == 0)
			end_node->left = nullptr;
		return 1;
	}

	void						erase(iterator i)
	{
		if (!deleteByVal(*i))
			return;
		tree_size--;
		if (tree_size == 0)
			end_node->left = nullptr;
	}

	void						erase(iterator first, iterator last)
	{	
		value_type v1 = *first, v2 = *(last), temp = v1;
		int i = 0;
		if (last._get_np() == get_end_node())
		{
			i = 1;
			v2 = tree_max(get_root())->val;
		}
		while (vc(v1, v2))
		{
			temp = tree_next(searchByVal(temp))->val;
			deleteByVal(v1);
			v1 = temp;
		}
		if (i == 1)
			deleteByVal(v2);
	}

    iterator  					find(const key_type& k)               
	{
		node_pointer	ret = searchByKey(k);

		if (!vc(ret->val, k) && !vc(k, ret->val))
			return iterator(ret);
		else	
			return end();
	}

    const_iterator  			find(const key_type& k) const           
	{
		node_pointer	ret = searchByKey(k);

		if (!vc(ret->val, k) && !vc(k, ret->val))
			return const_iterator(ret);
		else	
			return end();
	}

    size_type       			count(const key_type& k) const
	{
		const_node_pointer	ret = searchByKey(k);

		if (!vc(ret->val, k) && !vc(k, ret->val))
			return 1;
		else	
			return 0;
	}       

    iterator  					lower_bound(const key_type& k)
	{
		node_pointer	ret = searchByKey(k);

		if (!vc(ret->val, k))
			return iterator(ret);
		else 
			return iterator(tree_next(ret));
	}       

    const_iterator  			lower_bound(const key_type& k) const    
	{
		const_node_pointer	ret = searchByKey(k);

		if (!vc(ret->val, k))
			return const_iterator(ret);
		else 
			return const_iterator(tree_next(ret));
	}   

    iterator  					upper_bound(const key_type& k)
	{
		node_pointer	ret = searchByKey(k);

		if (vc(k, ret->val))
			return iterator(ret);
		else
			return iterator(tree_next(ret));
	}     

    const_iterator  			upper_bound(const key_type& k) const
	{
		const_node_pointer	ret = searchByKey(k);

		if (vc(k, ret->val))
			return const_iterator(ret);
		else
			return const_iterator(tree_next(ret));
	} 

    ft::pair<iterator,iterator>             equal_range(const key_type& k)
	{
		return ft::make_pair(static_cast<iterator>(lower_bound(k)), static_cast<iterator>(upper_bound(k)));
	}
    

    ft::pair<const_iterator,const_iterator> equal_range(const key_type& k) const
    {
		return ft::make_pair(static_cast<const_iterator>(lower_bound(k)), static_cast<const_iterator>(upper_bound(k)));
	}

private:
	void leftRotate(node_pointer x) 
	{
		node_pointer nParent = x->right;
		if (x == get_root())
			end_node->left = nParent;
		x->moveDown(nParent);
		x->right = nParent->left;
		if (nParent->left != nullptr)
			nParent->left->parent = x;
		nParent->left = x;
	}

	void rightRotate(node_pointer x) 
	{
		node_pointer nParent = x->left;
		if (x == get_root())
			end_node->left = nParent;
		x->moveDown(nParent);
		x->left = nParent->right;
		if (nParent->right != nullptr)
			nParent->right->parent = x;
		nParent->right = x;
	}

	void swapColors(node_pointer x1, node_pointer x2) 
	{
		COLOR temp;
		temp = x1->color;
		x1->color = x2->color;
		x2->color = temp;
	}

	void swapValues(node_pointer u, node_pointer v) 
	{
		Tp temp;
		temp = u->val;
		u->val = v->val;
		v->val = temp;
	}

	void fixRedRed(node_pointer x) 
	{
		// if x is root color it black and return
		if (x == get_root()) 
		{
			x->color = BLACK;
			return;
		}
		// initialize parent, grandparent, uncle
		node_pointer parent = x->parent, grandparent = parent->parent,
			 uncle = x->uncle();
		if (parent->color != BLACK) 
		{
			if (uncle != nullptr && uncle->color == RED) 
			{
				// uncle red, perform recoloring and recurse
				parent->color = BLACK;
				uncle->color = BLACK;
				grandparent->color = RED;
				fixRedRed(grandparent);
			} 
			else 
			{
				// Else perform LR, LL, RL, RR
				if (parent->isOnLeft()) 
				{
					if (x->isOnLeft()) 
					{
						// for left right
						swapColors(parent, grandparent);
					} 
					else 
					{
						leftRotate(parent);
						swapColors(x, grandparent);
					}
					// for left left and left right
					rightRotate(grandparent);
				} 
				else 
				{
					if (x->isOnLeft()) 
					{
						// for right left
						rightRotate(parent);
						swapColors(x, grandparent);
					} 
					else 
					{
						swapColors(parent, grandparent);
					}
					// for right right and right left
					leftRotate(grandparent);
				}
			}
		}
	}

	// find node that replaces a deleted node in BST
	node_pointer BSTreplace(node_pointer x) 
	{
		// when node have 2 children
		if (x->left != nullptr and x->right != nullptr)
			return tree_min(x->right);
		// when leaf
		if (x->left == nullptr and x->right == nullptr)
			return nullptr;
		// when single child
		if (x->left != nullptr)
			return x->left;
		else
			return x->right;
	}

	void deleteNode(node_pointer v) 
	{
		node_pointer u = BSTreplace(v);
		// True when u and v are both black
		bool uvBlack = ((u == nullptr or u->color == BLACK) && (v->color == BLACK));
		node_pointer parent = v->parent;
		if (u == nullptr) 
		{
			// u is nullptr therefore v is leaf
			if (v == get_root())
				end_node->left = nullptr;
			else 
			{
				if (uvBlack) 
				{
					// u and v both black
					// v is leaf, fix double black at v
					fixDoubleBlack(v);
				} 
				else 
				{
					// u or v is red
					if (v->sibling() != nullptr)
					{
						// sibling is not nullptr, make it red"
						v->sibling()->color = RED;
					}
				}
				// delete v from the tree
				if (v->isOnLeft()) 
					parent->left = nullptr;
				else 
					parent->right = nullptr;
			}
			destruct_node(v);
			return;
		}
		if (v->left == nullptr or v->right == nullptr) 
		{
			// v has 1 child
			if (v == get_root()) 
			{
				// v is root, assign the value of u to v, and delete u
				v->val = u->val;
				v->left = v->right = nullptr;
				destruct_node(u);
			} 
			else 
			{
				// Detach v from tree and move u up
				if (v->isOnLeft()) 
					parent->left = u;
				else
					parent->right = u;
				destruct_node(v);
				u->parent = parent;
				if (uvBlack) 
				{
					// u and v both black, fix double black at u
					fixDoubleBlack(u);
				} 
				else 
				{
					// u or v red, color u black
					u->color = BLACK;
				}
			}
			return;
		}
		// v has 2 children, swap values with successor and recurse
		swapValues(u, v);
		deleteNode(u);
	}

	void fixDoubleBlack(node_pointer x) 
	{
		if (x == get_root())
			return;
		node_pointer sibling = x->sibling(), parent = x->parent;
		if (sibling == nullptr) 
			fixDoubleBlack(parent);
		else 
		{
			if (sibling->color == RED) 
			{
				parent->color = RED;
				sibling->color = BLACK;
				if (sibling->isOnLeft()) 
					rightRotate(parent);
				else 
					leftRotate(parent);
				fixDoubleBlack(x);
			} 
			else 
			{
				if (sibling->hasRedChild()) 
				{
					// at least 1 red children
					if (sibling->left != nullptr and sibling->left->color == RED) 
					{
						if (sibling->isOnLeft()) 
						{
							sibling->left->color = sibling->color;
							sibling->color = parent->color;
							rightRotate(parent);
						} 
						else 
						{
							sibling->left->color = parent->color;
							rightRotate(sibling);
							leftRotate(parent);
						}
					} 
					else 
					{
						if (sibling->isOnLeft()) 
						{
							sibling->right->color = parent->color;
							leftRotate(sibling);
							rightRotate(parent);
						} 
						else 
						{
							sibling->right->color = sibling->color;
							sibling->color = parent->color;
							leftRotate(parent);
						}
					}
					parent->color = BLACK;
				} 
				else 
				{
					// 2 black children
					sibling->color = RED;
					if (parent->color == BLACK)
						fixDoubleBlack(parent);
					else
						parent->color = BLACK;
				}
			}
		}
	}

public:
	node_pointer searchByKey(const key_type& k)
	{
		node_pointer temp = get_root();
		while (temp != nullptr) 
		{
			if (vc(k, temp->val))  // k < (temp->val).first
			{
				if (temp->left == nullptr)
					break;
				else
					temp = temp->left;
			} 
			else if (!vc(temp->val, k) && !vc(k, temp->val))  // k == (temp->val).first
			{
				break;
			}
			else 
			{
				if (temp->right == nullptr)
					break;
				else
					temp = temp->right;
			}
		}
		return temp;
	}

	const_node_pointer searchByKey(const key_type& k) const
	{
		node_pointer temp = get_root();
		while (temp != nullptr) 
		{
			if (vc(k, temp->val))  // k < (temp->val).first
			{
				if (temp->left == nullptr)
					break;
				else
					temp = temp->left;
			} 
			else if (!vc(temp->val, k) && !vc(k, temp->val))  // k == (temp->val).first
			{
				break;
			}
			else 
			{
				if (temp->right == nullptr)
					break;
				else
					temp = temp->right;
			}
		}
		return static_cast<const_node_pointer>(temp);
	}

	node_pointer searchByVal(const value_type& n)
	{
		node_pointer temp = get_root();
		while (temp != nullptr) 
		{
			if (vc(n, temp->val))  // n < temp->val
			{
				if (temp->left == nullptr)
					break;
				else
					temp = temp->left;
			} 
			else if (!vc(temp->val, n) && !vc(n, temp->val))  // n == temp->val
			{
				break;
			}
			else 
			{
				if (temp->right == nullptr)
					break;
				else
					temp = temp->right;
			}
		}
		return temp;
	}

	node_pointer searchByVal(const_iterator i, const value_type& n)
	{
		if (i == end() || !vc(*i, n))	// n <= *i
		{
			const_iterator prior = i;
			if (prior == begin() || !vc(n, *--prior)) // *(--i) <= n
			{
				if (i._ptr->left == nullptr)
					return i._ptr; 		// place to insert is i._ptr->left
				else	
					return prior._ptr; 	// place to insert is prior._ptr->right
			}
			return searchByVal(n);
		}
		return searchByVal(n);
	}

	ft::pair<node_pointer, bool> insertByVal(const value_type& n) 
	{
		node_pointer newNode = construct_node(n);
		if (get_root() == nullptr) 
		{
			newNode->color = BLACK;
			end_node->left = newNode;
			newNode->parent = end_node;
		} 
		else 
		{
			node_pointer temp = searchByVal(n);
			if (!vc(temp->val, n) && !vc(n, temp->val))	// temp->val == n
			{	
				destruct_node(newNode);
				return ft::make_pair(temp, false);
			}
			newNode->parent = temp;
			if (vc(n, temp->val))	// n < temp->val
				temp->left = newNode;
			else
				temp->right = newNode;
			fixRedRed(newNode);
		}
		return ft::make_pair(newNode, true);
	}

	ft::pair<node_pointer, bool> insertByValInd(const_iterator i, const value_type& n) 
	{
		node_pointer newNode = construct_node(n);
		if (get_root() == nullptr) 
		{
			newNode->color = BLACK;
			end_node->left = newNode;
			newNode->parent = end_node;
		} 
		else 
		{
			node_pointer temp = searchByVal(i, n);
			if (!vc(temp->val, n) && !vc(n, temp->val)) // temp->val == n
			{	
				destruct_node(newNode);
				return ft::make_pair(temp, false);
			}
			newNode->parent = temp;
			if (vc(n, temp->val))  // n < temp->val
				temp->left = newNode;
			else
				temp->right = newNode;
			fixRedRed(newNode);
		}
		return ft::make_pair(newNode, true);
	}

	bool deleteByKey(const key_type& k) 
	{
		if (get_root() == nullptr)
			return false;
		node_pointer v = searchByKey(k);
		if (vc(v->val, k) || vc(k, v->val))  // (v->val).first != k
			return false;
		deleteNode(v);
		return true;
	}

	bool deleteByVal(const value_type& n) 
	{
		if (get_root() == nullptr)
			return false;
		node_pointer v = searchByVal(n);
		if (vc(v->val, n) || vc(n, v->val))  // v->val != n
			return false;
		deleteNode(v);
		return true;
	}

};

}

#endif
