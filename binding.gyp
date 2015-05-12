{
	'targets': [
		{
			'target_name': 'shm',
			'include_dirs': ["<!(node -e \"require('nan')\")"],
			'sources': [
				'shm.cc',
			]
		}
	]
}
