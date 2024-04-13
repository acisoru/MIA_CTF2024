const path              = require('path');
const express           = require('express');
const pug        		= require('pug');
// const handlebars        = require('handlebars');  I changed it
const { unflatten }     = require('flat');
const router            = express.Router();

router.get('/', (req, res) => {
    return res.sendFile(path.resolve('views/index.html'));
});

router.post('/api/submit', (req, res) => {
    const { secret } = unflatten(req.body);

    if (!/[\"@#%^*|/[^]|]/.test(secret.name)){
        if (secret.name.includes('Seek truth')) {
            return res.json({
                'response': pug.compile('Hello #{username}, thank you for proving that you are from our sorority! Seek truth together!')({ username:'alumna' })
            });
        } else {
            return res.json({
                'response': 'Seems like you do not belong to our society, get out of here!!!'
            });
        }
    } else {
        return res.json({
            'response': 'Hack was attempted. GO AWAY.'
        });
    }

});

module.exports = router;