graphic.setValue('led0', false);
graphic.setValue('led1', false);
graphic.setValue('led2', false);
graphic.setValue('led3', false);
graphic.setValue('led4', false);
graphic.setValue('led5', false);
graphic.setValue('led6', false);
graphic.setValue('led7', false);
graphic.setValue('sw0', false);
graphic.setValue('sw1', false);
graphic.setValue('sw2', false);
graphic.setValue('sw3', false);
graphic.setValue('sw4', false);
graphic.setValue('sw5', false);
graphic.setValue('sw6', false);
graphic.setValue('sw7', false);
// sw0
graphic.element('image701').on('click', function(element, event) {
    console.log('event: ' + event.type + ', element: ' + element.id);	
	var b1 = graphic.getValue('sw0');
	graphic.setValue('sw0',!b1);
	jp_setValue('sw0',!b1);
});
// sw1
graphic.element('image496').on('click', function(element, event) {
    console.log('event: ' + event.type + ', element: ' + element.id);	
	var b1 = graphic.getValue('sw1');	
	graphic.setValue('sw1',!b1);
	jp_setValue('sw1',!b1);
});
// sw2
graphic.element('image510').on('click', function(element, event) {
    console.log('event: ' + event.type + ', element: ' + element.id);	
	var b1 = graphic.getValue('sw2');
	graphic.setValue('sw2',!b1);
	jp_setValue('sw2',!b1);
});
// sw3
graphic.element('image524').on('click', function(element, event) {
    console.log('event: ' + event.type + ', element: ' + element.id);	
	var b1 = graphic.getValue('sw3');
	graphic.setValue('sw3',!b1);
	jp_setValue('sw3',!b1);
});
// sw4
graphic.element('image552').on('click', function(element, event) {
    console.log('event: ' + event.type + ', element: ' + element.id);	
	var b1 = graphic.getValue('sw4');
	graphic.setValue('sw4',!b1);
	jp_setValue('sw4',!b1);
});
// sw5
graphic.element('image566').on('click', function(element, event) {
    console.log('event: ' + event.type + ', element: ' + element.id);	
	var b1 = graphic.getValue('sw5');
	graphic.setValue('sw5',!b1);
	jp_setValue('sw5',!b1);
});
// sw6
graphic.element('image538').on('click', function(element, event) {
    console.log('event: ' + event.type + ', element: ' + element.id);	
	var b1 = graphic.getValue('sw6');
	graphic.setValue('sw6',!b1);
	jp_setValue('sw6',!b1);
});
// sw7
graphic.element('image580').on('click', function(element, event) {
    console.log('event: ' + event.type + ', element: ' + element.id);	
	var b1 = graphic.getValue('sw7');
	graphic.setValue('sw7',!b1);
	jp_setValue('sw7',!b1);
});
