default:
	: 'EXAMPLES:'
	: '    make build'
	: '    make install'
	: '    make uninstall'

.PHONY: build clean default install test uninstall

node_modules/.timestamp: package-lock.json
	npm ci
	mkdir -p node_modules && touch node_modules/.timestamp

milone-lang.vsix: node_modules/.timestamp \
		language-configuration.json \
		package.json \
		$(wildcard src/*.ts) \
		syntaxes/milone.json
	npm run webpack-prod
	npm run vsce-package

build: milone-lang.vsix

install: milone-lang.vsix
	code --install-extension milone-lang.vsix

uninstall:
	./uninstall || :
